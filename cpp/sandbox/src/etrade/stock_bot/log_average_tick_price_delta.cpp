#ifndef ETRADE__STOCK_BOT_log_average_tick_price_delta
#define ETRADE__STOCK_BOT_log_average_tick_price_delta

#include "lib/utils/integer.cpp" // utils::integer
#include "stock_bot.h"           // ETrade::StockBot, fmt
#include <iomanip>               // std::setprecision
#include <iostream>              // std::cout, std::endl, std::fixed

void ETrade::StockBot::log_average_tick_price_delta() {
  if (!this->average_tick_price_delta) {
    return;
  }

  const double price_range =
      this->moving_price_range.high - this->moving_price_range.low;

  std::cout << fmt.bold << fmt.underline << fmt.cyan;

  std::cout << "💲 Avg Tick Price Δ: ("
            << utils::integer_::seconds_to_clock(
                   this->AVERAGE_TICK_PRICE_DELTA_PERIOD)
            << ")";

  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.cyan << std::setprecision(4) << std::fixed;
  std::cout << "x1: " << this->average_tick_price_delta;
  std::cout << " • 5: " << (this->average_tick_price_delta * 5.0);
  std::cout << " • x10: " << (this->average_tick_price_delta * 10.0);
  std::cout << " • x25: " << (this->average_tick_price_delta * 25.0);
  std::cout << " • x33.3: "
            << (this->average_tick_price_delta * (1.0 / 3) * 100.0);

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif