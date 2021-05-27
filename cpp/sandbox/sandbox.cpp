#include "lib/websockets/client/client.cpp" // WebSockets::Client
#include <iostream>

int main() {
  WebSockets::Client client("wss://stream.data.alpaca.markets/v2/iex");
  client.connect();
}
