#if !defined ETRADE__STOCK_BOT_log_moving_price_range
#define ETRADE__STOCK_BOT_log_moving_price_range

#include "lib/utils/integer.cpp" // utils::integer
#include "stock_bot.h"           // ETrade::StockBot, fmt
#include <iostream>              // std::cout, std::endl
#include <math.h>                // INFINITY

void ETrade::StockBot::log_moving_price_range() {
  const double price_range =
      this->moving_price_range.high - this->moving_price_range.low;

  std::cout << fmt.bold << fmt.underline << fmt.cyan;
  std::cout << "💸 Period Price Range: ("
            << utils::integer_::seconds_to_clock(
                   this->moving_price_range.period)
            << ")";

  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "High: " << this->moving_price_range.high;
  std::cout << " • Low: " << this->moving_price_range.low;
  std::cout << " • Range: " << price_range;
  std::cout << std::endl;

  std::cout << "Max Loss: " << this->moving_price_range.max_loss;
  std::cout << " • Min Profit: " << this->moving_price_range.min_profit;
  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
