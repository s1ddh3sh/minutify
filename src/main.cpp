#include "dotenv.h"
#include <stdio.h>
#include <td/telegram/td_json_client.h>
#include <tgbot/tgbot.h>

int main() {
  TgBot::Bot bot(dotenv::getenv("BOT_TOKEN"));
  bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
  });
  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    if (StringTools::startsWith(message->text, "/start")) {
      return;
    }
    if (message->audio) {
      printf("Audio received. fileId: %s\n", message->audio->fileId.c_str());

      bot.getApi().sendMessage(message->chat->id,
                               "Hold On, Meeting minutes on the Way");

      TgBot::File::Ptr file = bot.getApi().getFile(message->audio->fileId);
      std::string audioData = bot.getApi().downloadFile(file->filePath);

      printf("Downloaded audio size: %zu bytes\n", audioData.size());
    } else {
      bot.getApi().sendMessage(message->chat->id,
                               "Please send an audio (m4a) file!");
    }
  });
  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      longPoll.start();
    }
  } catch (TgBot::TgException &e) {
    printf("error: %s\n", e.what());
  }
  return 0;
}