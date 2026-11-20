#include "ftpserver.h"

#if defined(USE_SD) && SDC_CS != 255 && (!defined(FTP_SERVER_ENABLED) || FTP_SERVER_ENABLED)
#include <algorithm>
#include "player.h"
#include "config.h"
#include "../displays/tools/l10n.h"

SDCardFTPServer ftpServer;

void SDCardFTPServer::begin() {
  // The FTP control service is independent of SD availability. The card is
  // mounted lazily when a client opens a control session.
  if (_started || WiFi.status() != WL_CONNECTED) return;
  _control.begin();
  _control.setNoDelay(true);
  _started = true;
  Serial.printf("##[FTP]# FTP control listening on port %u\n", FTP_SERVER_PORT);
}

void SDCardFTPServer::stop() {
  closeTransfer(false);
  if (_client) _client.stop();
  _control.stop();
  _passive.stop();
  _started = false;
}

void SDCardFTPServer::reply(uint16_t code, const String &message) {
  if (_client && _client.connected()) {
    _client.printf("%u %s\r\n", code, message.c_str());
  }
}

String SDCardFTPServer::normalizePath(const String &input) {
  String path = input;
  path.trim();
  if (path.length() == 0) path = _cwd;
  if (!path.startsWith("/")) path = _cwd + ( _cwd.endsWith("/") ? "" : "/" ) + path;

  String result = "/";
  int start = 1;
  while (start <= path.length()) {
    int end = path.indexOf('/', start);
    if (end < 0) end = path.length();
    String part = path.substring(start, end);
    if (part == "..") {
      int slash = result.lastIndexOf('/');
      result = slash > 0 ? result.substring(0, slash) : "/";
    } else if (part.length() && part != ".") {
      if (!result.endsWith("/")) result += "/";
      result += part;
    }
    start = end + 1;
  }
  if (result.length() > 1 && input.endsWith("/")) result += "/";
  return result;
}

void SDCardFTPServer::closeTransfer(bool success) {
  const bool completedUpload = success && _transfer == UPLOADING;
  if (_file) {
    if (_transfer == UPLOADING) _file.flush();
    _file.close();
  }
  if (_directory) _directory.close();
  if (_data) _data.stop();
  _transfer = IDLE;
  _pasv = false;
  if (completedUpload) {
    _indexDirty = true;
    _indexChangeAt = millis();
  }
  if (success) reply(226, "Transfer complete");
  else if (_client && _client.connected()) reply(426, "Transfer aborted");
}

void SDCardFTPServer::acceptData() {
  if (!_pasv || _data) return;
  WiFiClient incoming = _passive.accept();
  if (incoming) {
    _data = incoming;
    _data.setNoDelay(true);
    _passive.stop();
    _pasv = false;
  }
}

void SDCardFTPServer::startTransfer(Transfer transfer, const String &path, bool append) {
  if (!_loggedIn) { reply(530, "Please login"); return; }
  if (!sdman.ready) { reply(550, "No media"); return; }
  if (!_pasv) { reply(425, "Use PASV first"); return; }
  _pendingPath = normalizePath(path);
  _transfer = transfer;
  reply(150, "Opening data connection");
  acceptData();
  if (transfer == LISTING) {
    config.setTitle("[ F T P ]");
    _directory = sdman.open(_pendingPath);
    if (!_directory || !_directory.isDirectory()) { closeTransfer(false); reply(550, "Not a directory"); }
  } else if (transfer == DOWNLOADING) {
    _file = sdman.open(_pendingPath, FILE_READ);
    if (!_file || _file.isDirectory()) { closeTransfer(false); reply(550, "File unavailable"); }
  } else if (transfer == UPLOADING) {
    _file = sdman.open(_pendingPath, append ? FILE_APPEND : FILE_WRITE);
    if (!_file || _file.isDirectory()) { closeTransfer(false); reply(550, "Cannot create file"); }
  }
}

void SDCardFTPServer::sendListEntry(File &entry) {
  if (!_data || !entry) return;
  String name = entry.name();
  if (name.length() == 0) return;
  _data.printf("%s 1 ftp ftp %10u Jan  1 00:00 %s\r\n",
               entry.isDirectory() ? "drwxr-xr-x" : "-rw-r--r--",
               (unsigned)entry.size(), name.c_str());
}

void SDCardFTPServer::listStep() {
  if (!_directory || !_data) { closeTransfer(false); return; }
  // A small amount of work per loop keeps audio decoding responsive.
  for (uint8_t n = 0; n < 4; ++n) {
    bool isDir = false;
    String name = _directory.getNextFileName(&isDir);
    if (name.isEmpty()) { closeTransfer(true); return; }
    String full = name;
    File entry = sdman.open(full, FILE_READ);
    if (entry) {
      _data.printf("%s 1 ftp ftp %10u Jan  1 00:00 %s\r\n",
                   isDir ? "drwxr-xr-x" : "-rw-r--r--",
                   (unsigned)entry.size(),
                   full.substring(full.lastIndexOf('/') + 1).c_str());
      entry.close();
    }
  }
}

void SDCardFTPServer::transferStep() {
  if (_transfer == IDLE) return;
  // Wait until Player has processed PR_STOP before accessing the SD card.
  if (_resumeAfterFTP && player.status() != STOPPED) return;
  acceptData();

  // A passive connection may arrive after the 150 response. Wait while PASV
  // is armed; once a data socket was accepted, treat a closed socket as EOF.
  if (_transfer == UPLOADING) {
    if (!_data && _data.available() == 0) {
      if (!_pasv) closeTransfer(true);
      return;
    }
    // Drain several 2 KiB blocks per main-loop pass. This removes the
    // previous 512-byte-per-pass throughput ceiling while keeping a bound
    // on the time spent away from the audio decoder.
    for (uint8_t n = 0; n < 16; ++n) {
      int available = _data.available();
      if (available <= 0) break;
      size_t count = (size_t)available;
      if (count > sizeof(_buffer)) count = sizeof(_buffer);
      int got = _data.read(_buffer, count);
      if (got > 0 && _file.write(_buffer, (size_t)got) != (size_t)got) {
        closeTransfer(false);
        return;
      }
      if (got <= 0) break;
    }
    if (!_data.connected() && _data.available() == 0) closeTransfer(true);
    return;
  }

  if (!_data || !_data.connected()) {
    if (!_pasv) closeTransfer(false);
    return;
  }

  if (_transfer == LISTING) {
    listStep();
    return;
  }
  if (!_file) { closeTransfer(false); return; }

  if (_transfer == DOWNLOADING) {
    // Send up to 8 KiB per pass, yielding back to the radio loop regularly.
    for (uint8_t n = 0; n < 16; ++n) {
      size_t count = _file.read(_buffer, sizeof(_buffer));
      if (!count) {
        closeTransfer(true);
        return;
      }
      size_t sent = _data.write(_buffer, count);
      if (sent != count) { closeTransfer(false); return; }
    }
  }
}

void SDCardFTPServer::command(String line) {
  line.trim();
  if (!line.length()) return;
  int split = line.indexOf(' ');
  String verb = split < 0 ? line : line.substring(0, split);
  String arg = split < 0 ? "" : line.substring(split + 1);
  verb.toUpperCase();
  arg.trim();
  _lastActivity = millis();

  if (verb == "USER") {
    _userAccepted = (arg == FTP_USER);
    _loggedIn = false;
    reply(_userAccepted ? 331 : 530, _userAccepted ? "Password required" : "Invalid username");
  } else if (verb == "PASS") {
    _loggedIn = (_userAccepted && arg == FTP_PASSWORD);
    reply(_loggedIn ? 230 : 530, _loggedIn ? "Login successful" : "Login incorrect");
  } else if (verb == "QUIT") {
    reply(221, "Goodbye");
    closeTransfer(false);
    _client.stop();
    config.setTitle(LANG::const_PlStopped);
  } else if (verb == "SYST") reply(215, "UNIX Type: L8");
  else if (verb == "FEAT") {
    _client.print("211-Features\r\n PASV\r\n SIZE\r\n UTF8\r\n211 End\r\n");
  } else if (verb == "TYPE") reply(200, "Type set");
  else if (verb == "NOOP") reply(200, "OK");
  else if (verb == "PWD" || verb == "XPWD") reply(257, "\"" + _cwd + "\"");
  else if (!_loggedIn) reply(530, "Please login");
  else if (!sdman.ready &&
           (verb == "CWD" || verb == "XCWD" || verb == "LIST" || verb == "NLST" ||
            verb == "RETR" || verb == "STOR" || verb == "APPE" ||
            verb == "MKD" || verb == "XMKD" || verb == "RMD" || verb == "XRMD" ||
            verb == "DELE" || verb == "RNFR" || verb == "RNTO" || verb == "SIZE")) {
    reply(550, "No media");
  }
  else if (verb == "CWD" || verb == "XCWD") {
    String path = normalizePath(arg);
    File dir = sdman.open(path);
    if (dir && dir.isDirectory()) { _cwd = path; reply(250, "Directory changed"); }
    else reply(550, "Directory unavailable");
    if (dir) dir.close();
  } else if (verb == "CDUP") {
    _cwd = normalizePath("..");
    reply(250, "Directory changed");
  } else if (verb == "PASV") {
    if (_data) _data.stop();
    _passive.stop();
    _passive.begin();
    _passive.setNoDelay(true);
    _pasv = true;
    IPAddress ip = WiFi.localIP();
    reply(227, "Entering Passive Mode (" + String(ip[0]) + "," + String(ip[1]) + "," +
                 String(ip[2]) + "," + String(ip[3]) + "," +
                 String(FTP_PASSIVE_PORT / 256) + "," + String(FTP_PASSIVE_PORT % 256) + ")");
  } else if (verb == "LIST" || verb == "NLST") startTransfer(LISTING, arg);
  else if (verb == "RETR") startTransfer(DOWNLOADING, arg);
  else if (verb == "STOR") startTransfer(UPLOADING, arg, false);
  else if (verb == "APPE") startTransfer(UPLOADING, arg, true);
  else if (verb == "MKD" || verb == "XMKD") {
    String path = normalizePath(arg);
    reply(sdman.mkdir(path) ? 257 : 550, "Directory create");
  } else if (verb == "RMD" || verb == "XRMD") {
    String path = normalizePath(arg);
    reply(sdman.rmdir(path) ? 250 : 550, "Directory remove");
  } else if (verb == "DELE") {
    String path = normalizePath(arg);
    bool removed = sdman.remove(path);
    if (removed) {
      _indexDirty = true;
      _indexChangeAt = millis();
    }
    reply(removed ? 250 : 550, "File delete");
  } else if (verb == "RNFR") {
    _renameFrom = normalizePath(arg);
    reply(sdman.exists(_renameFrom) ? 350 : 550, "Send RNTO");
  } else if (verb == "RNTO") {
    String path = normalizePath(arg);
    bool renamed = _renameFrom.length() && sdman.rename(_renameFrom, path);
    if (renamed) {
      _indexDirty = true;
      _indexChangeAt = millis();
    }
    reply(renamed ? 250 : 550, "Rename");
    _renameFrom = "";
  } else if (verb == "SIZE") {
    File f = sdman.open(normalizePath(arg), FILE_READ);
    if (f) { reply(213, String((unsigned long)f.size())); f.close(); }
    else reply(550, "File unavailable");
  } else if (verb == "ABOR") {
    closeTransfer(false);
    reply(226, "Abort successful");
  } else reply(502, "Command not implemented");
}

void SDCardFTPServer::loop() {
  if (!_started) {
    begin();
    return;
  }
  if (WiFi.status() != WL_CONNECTED) {
    stop();
    return;
  }
  if (_client && !_client.connected()) {
    closeTransfer(false);
    _client.stop();
    _loggedIn = false;
    if (_resumeAfterFTP) {
      _resumeCommandSent = false;
      _resumeAttempts = 0;
      Serial.printf("##[FTP]# FTP disconnected; scheduling playback resume at station %u\n", _resumeStation);
    }
  }
  if ((!_client || !_client.connected()) && !_resumeAfterFTP) {
    _client = _control.accept();
    if (_client) {
      _client.setNoDelay(true);
      _loggedIn = false;
      _userAccepted = false;
      _resumeAttempts = 0;
      _resumeCommandSent = false;
      _cwd = "/";
      _line = "";
      _mountPending = !sdman.ready;
      // Give FTP exclusive access to the SD card and CPU while connected.
      // Remember playback only if it was active before this FTP session.
      _resumeAfterFTP = player.status() == PLAYING;
      if (_resumeAfterFTP) {
        _resumeStation = config.lastStation();
        player.sendCommand({PR_STOP, 0});
        Serial.println("##[FTP]# Playback paused for FTP transfer");
      }
      reply(220, "yoRadio SD FTP ready");
    }
  }

  // Mount only once per new FTP session, and only after playback has stopped.
  // This keeps SD initialization out of the audio path and avoids retry loops.
  if (_mountPending) {
    if (player.status() != STOPPED) return;
    _mountPending = false;
    if (sdman.start()) {
      Serial.println("##[FTP]# SD card mounted for FTP session");
    } else {
      Serial.println("##[FTP]# No SD media available for this FTP session");
    }
  }

  if (_client && _client.connected()) {
    uint8_t budget = 128;
    while (_client.available() && budget--) {
      char c = (char)_client.read();
      if (c == '\n') {
        command(_line);
        _line = "";
      } else if (c != '\r' && _line.length() < 512) _line += c;
    }
    config.screensaverTicks=SCREENSAVERSTARTUPDELAY;
    config.screensaverPlayingTicks=SCREENSAVERSTARTUPDELAY;    
  }
  transferStep();

  // yoRadio reads the SD playlist from PLAYLIST_SD_PATH / INDEX_SD_PATH.
  // Retry the resume request if the player command queue did not accept it
  // or playback did not start. Keep the original station until PLAYING.
  if (_resumeAfterFTP && _resumeStation == 0) {
    _resumeAfterFTP = false;
    Serial.println("##[FTP]# Cannot resume playback: saved station is 0");
  }
  if (_resumeAfterFTP && (!_client || !_client.connected()) && _resumeStation > 0) {
    if (player.status() == PLAYING) {
      _resumeAfterFTP = false;
      _resumeCommandSent = false;
      Serial.println("##[FTP]# Playback resumed");
    } else if (!_resumeCommandSent || millis() - _resumeCommandAt >= 2500) {
      if (_resumeAttempts < 3) {
        player.sendCommand({PR_PLAY, (int)_resumeStation});
        _resumeCommandSent = true;
        _resumeCommandAt = millis();
        ++_resumeAttempts;
        Serial.printf("##[FTP]# Resume request %u for station %u\n", _resumeAttempts, _resumeStation);
      } else {
        _resumeAfterFTP = false;
        Serial.println("##[FTP]# Playback resume failed after 3 attempts");
      }
    }
  }

  // Debounce playlist rebuilding: wait until file operations have been idle
  // for FTP_INDEX_IDLE_MS, so uploading a directory triggers one scan.
  if (_indexDirty && _transfer == IDLE && sdman.ready &&
      millis() - _indexChangeAt >= FTP_INDEX_IDLE_MS) {
    _indexDirty = false;
    Serial.println("##[FTP]# Rebuilding SD audio playlist index");
    sdman.indexSDPlaylist();
    Serial.println("##[FTP]# SD audio playlist index updated");
  }
}
#endif
