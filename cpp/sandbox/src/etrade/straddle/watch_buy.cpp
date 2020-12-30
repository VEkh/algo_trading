#if !defined ETRADE__STRADDLE_watch_buy
#define ETRADE__STRADDLE_watch_buy

/*
 * ETrade::Straddle
 * buy_open_order
 * buy_profit_order
 * order_status_t
 * symbol
 */
#include "straddle.h"

#include "cancel_order.cpp"     // cancel_order
#include "get_order_status.cpp" // get_order_status
#include "lib/formatted.cpp"    // Formatted
#include "order_to_string.cpp"  // order_to_string
#include "place_order.cpp"      // place_order
#include <iostream>             // std::cout, std::endl

void ETrade::Straddle::watch_buy() {
  Formatted::fmt_stream_t fmt = stream_format;

  if (buy_open_order.id &&
      buy_open_order.status == order_status_t::ORDER_OPEN) {
    const char *status = get_order_status(buy_open_order);

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      buy_open_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "📈 BUY: Opened: \n" << std::endl;
      std::cout << order_to_string(buy_open_order) << std::endl;
      std::cout << fmt.reset;

      place_order(buy_profit_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "BUY: Placed the profit order: \n" << std::endl;
      std::cout << order_to_string(buy_profit_order) << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }

  if (buy_profit_order.id &&
      buy_profit_order.status == order_status_t::ORDER_OPEN) {
    const char *status = get_order_status(buy_profit_order);
    double current_price = quote["lastPrice"];

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      buy_profit_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "🎉 BUY: Profit order executed: \n" << std::endl;
      std::cout << order_to_string(buy_profit_order) << std::endl;
      std::cout << fmt.reset;

      cancel_order(sell_short_open_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "BUY: Cancelled the SELL_SHORT open order: \n" << std::endl;
      std::cout << order_to_string(sell_short_open_order) << std::endl;
      std::cout << fmt.reset;
    } else if (current_price <= buy_stop_loss_order.stop_price) {
      std::cout << fmt.bold << fmt.red << std::endl;
      std::cout << "😭 BUY: Price passed stop loss threshold. Cancelling profit "
                   "order: \n"
                << std::endl;
      std::cout << order_to_string(buy_profit_order) << std::endl;
      std::cout << fmt.reset;

      cancel_order(buy_profit_order);
      place_order(buy_stop_loss_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "BUY: Placed the stop loss order: \n" << std::endl;
      std::cout << order_to_string(buy_profit_order) << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }

  if (buy_stop_loss_order.id &&
      buy_stop_loss_order.status == order_status_t::ORDER_OPEN) {
    const char *status = get_order_status(buy_stop_loss_order);

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      buy_stop_loss_order.status == order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.red << std::endl;
      std::cout << "😭 BUY: Stop loss order executed: \n" << std::endl;
      std::cout << order_to_string(buy_stop_loss_order) << std::endl;

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "Better luck next time!" << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }
}

#endif
