#ifndef WEBSOCKETS__STATICS_connect_client
#define WEBSOCKETS__STATICS_connect_client

/*
 LibWebsockets:
 * lws_client_connect_info
 * lws_client_connect_via_info
 * lws_container_of
 * lws_retry_sul_schedule
 * lws_sorted_usec_list_t
 * lwsl_err
 */
#include "deps.cpp"

#include "global.cpp" // WebSockets::Statics
#include <cstring>    // memset

namespace WebSockets {
namespace Statics {
static void connect_client(lws_sorted_usec_list_t *scheduler) {
  struct connection *conn =
      lws_container_of(scheduler, struct connection, scheduler);
  struct lws_client_connect_info i;

  memset(&i, 0, sizeof(i));

  i.context = WebSockets::Statics::context;
  i.port = WebSockets::Statics::port;
  i.address = "yerrr"; // TODO: Get from Client
  i.path = "/";
  i.host = i.address;
  i.origin = i.address;
  i.ssl_connection = WebSockets::Statics::ssl_connection;
  i.protocol = WebSockets::Statics::protocol;
  i.local_protocol_name = "lws-minimal-client";
  i.pwsi = &conn->wsi;
  i.retry_and_idle_policy = &(WebSockets::Statics::retry);
  i.userdata = conn;

  if (!lws_client_connect_via_info(&i)) {
    /*
     * Failed... schedule a retry... we can't use the _retry_wsi()
     * convenience wrapper api here because no valid wsi at this
     * point.
     */
    if (lws_retry_sul_schedule(WebSockets::Statics::context, 0, scheduler,
                               &(WebSockets::Statics::retry), connect_client,
                               &conn->retry_count)) {
      lwsl_err("%s: connection attempts exhausted\n", __func__);
      WebSockets::Statics::interrupted = 1;
    }
  }
}
} // namespace Statics
} // namespace WebSockets
#endif
