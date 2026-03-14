#include "td_client.h"

#include <iostream>
#include <td/telegram/td_json_client.h>
#include <thread>

TDClient::TDClient() { client = td_json_client_create(); }

void TDClient::start() { td_json_client_send(client, R"()"); }


