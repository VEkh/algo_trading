#ifndef WEBSOCKETS__STATICS_callback_minimal
#define WEBSOCKETS__STATICS_callback_minimal

#include "global.cpp" // WebSockets::Statics

namespace WebSockets {
namespace Statics {
static int callback_minimal(struct lws *wsi, enum lws_callback_reasons reason,
                            void *user, void *in, size_t len) {
  struct my_conn *mco = (struct my_conn *)user;

  switch (reason) {

  case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
    lwsl_err("CLIENT_CONNECTION_ERROR: %s\n", in ? (char *)in : "(null)");
    goto do_retry;
    break;

  case LWS_CALLBACK_CLIENT_RECEIVE:
    lwsl_hexdump_notice(in, len);
    break;

  case LWS_CALLBACK_CLIENT_ESTABLISHED:
    lwsl_user("%s: established\n", __func__);
    break;

  case LWS_CALLBACK_CLIENT_CLOSED:
    goto do_retry;

  default:
    break;
  }

  return lws_callback_http_dummy(wsi, reason, user, in, len);

do_retry:
  /*
   * retry the connection to keep it nailed up
   *
   * For this example, we try to conceal any problem for one set of
   * backoff retries and then exit the app.
   *
   * If you set retry.conceal_count to be larger than the number of
   * elements in the backoff table, it will never give up and keep
   * retrying at the last backoff delay plus the random jitter amount.
   */
  if (lws_retry_sul_schedule_retry_wsi(wsi, &mco->sul, connect_client,
                                       &mco->retry_count)) {
    lwsl_err("%s: connection attempts exhausted\n", __func__);
    interrupted = 1;
  }

  return 0;
}
} // namespace Statics
} // namespace WebSockets
}

#endif
