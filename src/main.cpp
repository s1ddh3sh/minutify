#include "td_client.h"
#include "dotenv.h"

int main() {

    std::string token = dotenv::getenv("BOT_TOKEN");

    TDBot bot(token);

    bot.loop();

    return 0;
}