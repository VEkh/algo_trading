#if !defined WEBSOCKETS__CLIENT_connect
#define WEBSOCKETS__CLIENT_connect

#include "client.h"                                  // WebSockets::Client
#include "lib/websockets/statics/connect_client.cpp" // connect_client
#include <iostream>                                  // std::cout, std::endl

void WebSockets::Client::connect() {
  std::cout << "Connecting to: " << this->server_address << std::endl;
}

#endif
