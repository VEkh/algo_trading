#include "client/client.cpp"   // ETrade::Client
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/debug.cpp" // utils::debug
#include <iostream>            // std::cout, std::endl
#include <map>                 // std::map
#include <sstream>             // std::ostringstream
#include <string>              // std::string

void print_usage() {
  std::map<std::string, const char *> commands = {
      {"fetch_access_token          ", "Get authorization token"},
      {"fetch_quote <SYMBOL>        ", "Get quote for the given symbol"},
      {"refresh_token               ", "Refresh authorization tokens"},
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::ostringstream message;

  message << fmt.bold << fmt.cyan << "E*TRADE Client Usage:" << std::endl;

  std::map<std::string, const char *>::iterator it;
  for (it = commands.begin(); it != commands.end(); ++it) {
    message << fmt.bold << fmt.yellow << it->first << fmt.reset << " | "
            << it->second << std::endl;
  }

  std::cout << message.str();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage();
    exit(1);
  }

  std::string command = argv[1];

  if (command == "fetch_access_token") {
    ETrade::Client etrade_client;
    etrade_client.fetch_access_token();

    exit(0);
  }

  if (command == "fetch_quote") {
    ETrade::Client etrade_client;
    char *symbol = argc < 3 ? nullptr : argv[2];

    std::string quote = etrade_client.fetch_quote(symbol);
    std::cout << quote;

    exit(0);
  }

  if (command == "refresh_token") {
    ETrade::Client etrade_client;
    etrade_client.refresh_token();

    exit(0);
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red << "Unknown command <" << command
            << ">. Please refer to usage👇🏾\n"
            << fmt.reset << std::endl;

  print_usage();
  exit(127);
}
