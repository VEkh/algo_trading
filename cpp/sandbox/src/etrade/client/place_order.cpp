#ifndef ETRADE__CLIENT_place_order
#define ETRADE__CLIENT_place_order

#include "build_place_order_payload.cpp" // build_place_order_payload
#include "client.h"        // ETrade::Client, client_config, order_t
#include "etrade/deps.cpp" // json
#include "handle_place_order_error.cpp"           // handle_place_order_error
#include "is_next_cycle_retry_error.cpp"          // is_next_cycle_retry_error
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "preview_order.cpp"                      // preview_order
#include <regex>  // std::regex, std::regex_search
#include <time.h> // time, time_t

namespace ETrade {
namespace place_order {
bool is_immediate_retry_error(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::cout << fmt.yellow << response_body << fmt.reset << std::endl;

  if (std::regex_search(response_body,
                        std::regex("oauth_parameters_absent=oauth_nonce"))) {
    return true;
  }

  return false;
}
} // namespace place_order
} // namespace ETrade

CurlClient ETrade::Client::place_order(order_t *order) {
  std::string request_url = client_config.base_url + "/v1/accounts/" +
                            client_config.account_id_key + "/orders/place.json";

  CurlClient preview_curl_client = preview_order(*order);

  if (is_next_cycle_retry_error(preview_curl_client)) {
    return preview_curl_client;
  }

  std::string payload =
      build_place_order_payload(preview_curl_client.response.body);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return post({
            .body = payload,
            .method = CurlClient::http_method_t::POST,
            .url = request_url,
        });
      },
      ETrade::place_order::is_immediate_retry_error);

  curl_client = handle_place_order_error(curl_client, order->action, "Place");

  if (is_next_cycle_retry_error(curl_client)) {
    return curl_client;
  }

  time_t now;
  time(&now);

  json response = json::parse(curl_client.response.body);

  order->id = response["PlaceOrderResponse"]["OrderIds"][0]["orderId"];
  order->status = order_status_t::ORDER_OPEN;
  order->timestamp = now;

  return curl_client;
}

#endif
