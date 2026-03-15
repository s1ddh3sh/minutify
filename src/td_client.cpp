#include "td_client.h"
#include "td/telegram/td_json_client.h"
#include <dotenv.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>

using json = nlohmann::json;

TDBot::TDBot(const std::string &botToken) {

  token = botToken;
  client = td_json_client_create();

  json log = {{"@type", "setLogVerbosityLevel"}, {"new_verbosity_level", 1}};

  send(log.dump());

  json params = {{"@type", "setTdlibParameters"},
                 {"parameters",
                  {{"database_directory", "td-db"},
                   {"use_message_database", false},
                   {"use_secret_chats", false},
                   {"api_id", dotenv::getenv("TD_API_ID")},
                   {"api_hash", dotenv::getenv("TD_API_HASH")},
                   {"system_language_code", "en"},
                   {"device_model", "server"},
                   {"application_version", "1.0"}}}};

  send(params.dump());

  json auth = {{"@type", "checkAuthenticationBotToken"}, {"token", token}};

  send(auth.dump());
}

TDBot::~TDBot() { td_json_client_destroy(client); }

void TDBot::send(const std::string &query) {
  td_json_client_send(client, query.c_str());
}

std::string TDBot::receive(double timeout) {

  const char *res = td_json_client_receive(client, timeout);
  if (res)
    return std::string(res);
  return "";
}

void TDBot::sendMessage(int64_t chat_id, const std::string &text) {

  json q = {{"@type", "sendMessage"},
            {"chat_id", chat_id},
            {"input_message_content",
             {{"@type", "inputMessageText"},
              {"text", {{"@type", "formattedText"}, {"text", text}}}}}};

  send(q.dump());
}

void TDBot::downloadFile(int file_id) {

  json q = {{"@type", "downloadFile"},
            {"file_id", file_id},
            {"priority", 1},
            {"synchronous", false}};

  send(q.dump());
}

void TDBot::processUpdate(const std::string &jsonStr) {
  auto j = json::parse(jsonStr);

  if (j["@type"] != "updateNewMessage")
    return;

  auto msg = j["message"];

  int64_t chat_id = msg["chat_id"];

  if (!msg.contains("content"))
    return;

  auto content = msg["content"];

  if (content["@type"] == "messageText") {

    std::string text = content["text"]["text"];

    if (text == "/start") {
      sendMessage(chat_id, "Hi!");
      return;
    }
  }

  if (content["@type"] == "messageAudio") {

    int file_id = content["audio"]["audio"]["id"];

    std::cout << "Audio received. file_id=" << file_id << std::endl;

    sendMessage(chat_id, "Downloading audio...");

    downloadFile(file_id);
  }
}

void TDBot::loop() {

  while (true) {

    std::string res = receive();

    if (res.empty())
      continue;

    processUpdate(res);

    auto j = json::parse(res);

    if (j["@type"] == "updateFile") {

      auto file = j["file"];

      if (file["local"]["is_downloading_completed"]) {

        std::string path = file["local"]["path"];

        std::cout << "Downloaded file: " << path << std::endl;
      }
    }
  }
}