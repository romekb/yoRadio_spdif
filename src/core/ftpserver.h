#pragma once
#include "options.h"

#if defined(USE_SD) && SDC_CS != 255 && (!defined(FTP_SERVER_ENABLED) || FTP_SERVER_ENABLED)
#include <WiFi.h>
#include <SD.h>
#include <FS.h>
#include "sdmanager.h"

#ifndef FTP_INDEX_IDLE_MS
#define FTP_INDEX_IDLE_MS 5000
#endif
#ifndef FTP_SERVER_PORT
#define FTP_SERVER_PORT 21
#endif
#ifndef FTP_PASSIVE_PORT
#define FTP_PASSIVE_PORT 50009
#endif
#ifndef FTP_USER
#define FTP_USER "yoradio"
#endif
#ifndef FTP_PASSWORD
#define FTP_PASSWORD "yoradio"
#endif

class SDCardFTPServer {
 public:
  void loop();
  void begin();
  void stop();

 private:
  enum Transfer : uint8_t { IDLE, LISTING, DOWNLOADING, UPLOADING };
  WiFiServer _control{FTP_SERVER_PORT};
  WiFiServer _passive{FTP_PASSIVE_PORT};
  WiFiClient _client, _data;
  File _file, _directory;
  Transfer _transfer = IDLE;
  String _cwd = "/";
  String _pendingPath, _renameFrom;
  String _line;
  bool _started = false, _loggedIn = false, _userAccepted = false, _pasv = false;
  uint32_t _lastMountAttempt = 0;
  bool _indexDirty = false;
  uint32_t _indexChangeAt = 0;
  bool _resumeCommandSent = false;
  uint32_t _resumeCommandAt = 0;
  uint8_t _resumeAttempts = 0;
  bool _resumeAfterFTP = false;
  uint16_t _resumeStation = 0;
  uint32_t _lastActivity = 0;
  uint8_t _buffer[8192];

  void command(String line);
  void reply(uint16_t code, const String &message);
  String normalizePath(const String &path);
  void startTransfer(Transfer transfer, const String &path, bool append = false);
  void acceptData();
  void transferStep();
  void closeTransfer(bool success);
  void listStep();
  void sendListEntry(File &entry);
};

extern SDCardFTPServer ftpServer;
#endif
