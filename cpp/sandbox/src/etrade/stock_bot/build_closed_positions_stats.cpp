#ifndef ETRADE__STOCK_BOT_build_closed_positions_stats
#define ETRADE__STOCK_BOT_build_closed_positions_stats

/*
 * ETrade::StockBot
 * order_t
 * order_win_result_t
 * position_t
 */
#include "stock_bot.h"

#include "order_win_result.cpp" // order_win_result
#include <map>                  // std::map

ETrade::StockBot::closed_positions_stats_t
ETrade::StockBot::build_closed_positions_stats() {
  std::map<order_win_result_t, int> results = {
      {order_win_result_t::LOSS, 0},
      {order_win_result_t::TIE, 0},
      {order_win_result_t::WIN, 0},
  };

  bool loss_streak_broken = false;
  bool win_streak_broken = false;
  double total_profit = 0.00;
  int l = this->closed_positions.size();
  int loss_streak = 0;
  int win_streak = 0;

  for (int i = l - 1; i > -1; i--) {
    const position_t position = this->closed_positions[i];
    const order_win_result_t result = order_win_result(&(position.close_order));
    results[result]++;
    total_profit += position.close_order.profit * position.close_order.quantity;

    loss_streak_broken =
        loss_streak_broken || result == order_win_result_t::WIN;

    win_streak_broken = win_streak_broken || result == order_win_result_t::LOSS;

    if (result == order_win_result_t::WIN && !win_streak_broken) {
      win_streak++;
    } else if (result == order_win_result_t::LOSS && !loss_streak_broken) {
      loss_streak++;
    }
  }

  std::cout << fmt.yellow << fmt.bold;
  std::cout << "Profits: [";

  for (int i = 0; i < l; i++) {
    const position_t position = this->closed_positions[i];

    if (i != 0) {
      std::cout << ", ";
    }

    std::cout << position.close_order.profit << ":"
              << position.close_order.quantity;
  }

  std::cout << "]" << std::endl;
  std::cout << fmt.reset;

  return {
      .results = results,
      .loss_streak = loss_streak,
      .total_profit = total_profit,
      .win_streak = win_streak,
  };
}

#endif
