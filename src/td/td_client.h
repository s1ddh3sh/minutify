#pragma once
#include "string"
#include <string>

class TDClient {
public:
  TDClient();

  void start();

  void downloadFile(std::string &fileId);

private:
  void *client;
};