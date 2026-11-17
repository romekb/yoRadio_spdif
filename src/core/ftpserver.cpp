#include "ftpserver.h"

#if defined(USE_SD) && SDC_CS != 255 && (!defined(FTP_SERVER_ENABLED) || FTP_SERVER_ENABLED)
#include <algorithm>

SDCardFTPServer ftpServer;

void SDCardFTPServer::begin() {
  if (_started || !sdman.ready || WiFi.status() != WL_CONNECTED) return;
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
      int slash = result.lastIndexOf('/', result.length() - 2);
      result = slash >= 0 ? result.substring(0, slash + 1) : "/";
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
  if (_file) {
    if (_transfer == UPLOADING) _file.flush();
    _file.close();
  }
  if (_directory) _directory.close();
  if (_data) _data.stop();
  _transfer = IDLE;
  _pasv = false;
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

void SDCardFTPServer::startTransfer(Transfer transfer, const String &path) {
  if (!_loggedIn) { reply(530, "Please login"); return; }
  if (!_pasv) { reply(425, "Use PASV first"); return; }
  _pendingPath = normalizePath(path);
  _transfer = transfer;
  reply(150, "Opening data connection");
  acceptData();
  if (transfer == LISTING) {
    _directory = sdman.open(_pendingPath);
    if (!_directory || !_directory.isDirectory()) { closeTransfer(false); reply(550, "Not a directory"); }
  } else if (transfer == DOWNLOADING) {
    _file = sdman.open(_pendingPath, FILE_READ);
    if (!_file || _file.isDirectory()) { closeTransfer(false); reply(550, "File unavailable"); }
  } else if (transfer == UPLOADING) {
    _file = sdman.open(_pendingPath, FILE_WRITE);
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
  acceptData();
  if (!_data || !_data.connected()) return;

  if (_transfer == LISTING) {
    listStep();
    return;
  }
  if (!_file) { closeTransfer(false); return; }

  if (_transfer == DOWNLOADING) {
    size_t count = _file.read(_buffer, sizeof(_buffer));
    if (count) {
      size_t sent = _data.write(_buffer, count);
      if (sent != count) { closeTransfer(false); return; }
    } else {
      closeTransfer(true);
    }
  } else if (_transfer == UPLOADING) {
    int available = _data.available();
    if (available > 0) {
      size_t count = (size_t)available;
      if (count > sizeof(_buffer)) count = sizeof(_buffer);
      int got = _data.read(_buffer, count);
      if (got > 0 && _file.write(_buffer, (size_t)got) != (size_t)got) {
        closeTransfer(false);
        return;
      }
    } else if (!_data.connected()) {
      closeTransfer(true);
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
    _loggedIn = false;
    reply(331, "Password required");
  } else if (verb == "PASS") {
    _loggedIn = (arg == FTP_PASSWORD);
    reply(_loggedIn ? 230 : 530, _loggedIn ? "Login successful" : "Login incorrect");
  } else if (verb == "QUIT") {
    reply(221, "Goodbye");
    closeTransfer(false);
    _client.stop();
  } else if (verb == "SYST") reply(215, "UNIX Type: L8");
  else if (verb == "FEAT") {
    _client.print("211-Features\r\n PASV\r\n SIZE\r\n UTF8\r\n211 End\r\n");
  } else if (verb == "TYPE") reply(200, "Type set");
  else if (verb == "NOOP") reply(200, "OK");
  else if (verb == "PWD" || verb == "XPWD") reply(257, "\"" + _cwd + "\"");
  else if (!_loggedIn) reply(530, "Please login");
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
  else if (verb == "STOR") startTransfer(UPLOADING, arg);
  else if (verb == "MKD" || verb == "XMKD") {
    String path = normalizePath(arg);
    reply(sdman.mkdir(path) ? 257 : 550, "Directory create");
  } else if (verb == "RMD" || verb == "XRMD") {
    String path = normalizePath(arg);
    reply(sdman.rmdir(path) ? 250 : 550, "Directory remove");
  } else if (verb == "DELE") {
    String path = normalizePath(arg);
    reply(sdman.remove(path) ? 250 : 550, "File delete");
  } else if (verb == "RNFR") {
    _renameFrom = normalizePath(arg);
    reply(sdman.exists(_renameFrom) ? 350 : 550, "Send RNTO");
  } else if (verb == "RNTO") {
    String path = normalizePath(arg);
    reply(_renameFrom.length() && sdman.rename(_renameFrom, path) ? 250 : 550, "Rename");
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
  if (WiFi.status() != WL_CONNECTED || !sdman.ready) {
    stop();
    return;
  }
  if (_client && !_client.connected()) {
    closeTransfer(false);
    _client.stop();
    _loggedIn = false;
  }
  if (!_client || !_client.connected()) {
    _client = _control.accept();
    if (_client) {
      _client.setNoDelay(true);
      _loggedIn = false;
      _cwd = "/";
      _line = "";
      reply(220, "yoRadio SD FTP ready");
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
  }
  transferStep();
}
#endif
