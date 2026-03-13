#include <stdio.h>
#include <tgbot/tgbot.h>

int main() {
  TgBot::Bot bot(getenv("BOT_TOKEN"));
  bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
  });
  bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
    if (StringTools::startsWith(message->text, "/start")) {
      return;
    }
    if (message->audio) {
      printf("Yep its a audio file %s\n", message->audio->fileName.c_str());
      bot.getApi().sendMessage(message->chat->id,
                               "Hold On, Meeting minutes on the Way");
    } else {
      bot.getApi().sendMessage(message->chat->id,
                               "Please enter audio(m4a) file!");
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