#if !defined WEBSOCKETS__CLIENT_H
#define WEBSOCKETS__CLIENT_H

/*
 LibWebsockets:
 * lws
 * lws_callback_reasons
 * lws_sorted_usec_list_t
 */
#include "deps.cpp"

namespace WebSockets {
class Client {
public:
  Client(const char *server_address_)
      : server_address((char *)server_address_){};

  void connect();

private:
  char *server_address;

  int callback_minimal(struct lws *, enum lws_callback_reasons, void *, void *,
                       size_t);

  static void connect_client(lws_sorted_usec_list_t *);
};
} // namespace WebSockets

#endif
