#if !defined ETRADE__STOCK_BOT_H
#define ETRADE__STOCK_BOT_H

#include "etrade/client/client.h"             // ETrade::Client
#include "etrade/deps.cpp"                    // json, _json
#include "etrade/speedometer/speedometer.cpp" // ETrade::Speedometer
#include "lib/formatted.cpp"                  // Formatted

using order_action_t = ETrade::Client::order_action_t;
using order_status_t = ETrade::Client::order_status_t;
using order_t = ETrade::Client::order_t;
using order_type_t = ETrade::Client::order_type_t;

namespace ETrade {
class StockBot {
public:
  enum status_t {
    CLOSED,
    COMPLETE,
    LIMBO,
    OPEN,
    PENDING,
  };

  StockBot(char *);
  StockBot(char *, int);
  StockBot(char *, int, char *);

  char *next_order_action = nullptr;
  void run();

private:
  const double POLLING_INTERVAL_SECONDS = 0.5;

  char *init_order_action = nullptr;
  char *symbol;
  double day_range;
  int quantity;

  ETrade::Client etrade_client;
  ETrade::Speedometer speedometer = ETrade::Speedometer(&quotes);
  Formatted::fmt_stream_t stream_format = Formatted::stream();

  json placed_orders;
  json quotes = R"([])"_json;

  order_t buy_open_order;
  order_t buy_close_order;
  order_t sell_short_open_order;
  order_t sell_short_close_order;

  json get_order_json(const order_t &);

  status_t status();

  double compute_door_delta();
  double compute_trailing_stop(const order_t *, const double);

  void fetch_and_set_orders();
  void fetch_and_set_quote();
  void initialize(char *, int);
  void log_prices();
  void log_start_message();
  void log_status();
  void set_order_prices();
  void set_execution_price(order_t *);
  void set_profit(order_t *);
  void set_profit(order_t *, const order_t *);
  void set_status(order_t *);
  void set_trailing_stop_price(order_t *, const order_t *);
  void watch();
  void watch_side(const order_action_t &);
};
} // namespace ETrade

#endif