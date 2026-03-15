#pragma once

#include <string>
#include <td/telegram/td_json_client.h>

class TDBot {
public:
    TDBot(const std::string &botToken);
    ~TDBot();

    void loop();

private:
    void *client;
    std::string token;

    void send(const std::string &query);
    std::string receive(double timeout = 1.0);

    void processUpdate(const std::string &jsonStr);

    void sendMessage(int64_t chat_id, const std::string &text);
    void downloadFile(int file_id);
};