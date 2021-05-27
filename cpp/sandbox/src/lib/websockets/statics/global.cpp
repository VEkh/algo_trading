#ifndef WEBSOCKETS__STATICS__global
#define WEBSOCKETS__STATICS__global

/*
 LibWebsockets:
 * LCCSCF_USE_SSL
 * LWS_ARRAY_SIZE
 * lws
 * lws_context
 * lws_retry_bo_t
 * lws_sorted_usec_list_t
 */
#include "deps.cpp"

namespace WebSockets {
namespace Statics {
static struct connection {
  lws_sorted_usec_list_t scheduler;
  struct lws *wsi;
  uint16_t retry_count;
} conn;

static struct lws_context *context;

static const char *protocol = "dumb-increment-protocol";
static const uint32_t backoff_ms[] = {1000, 2000, 3000, 4000, 5000};

static int interrupted = 0;
static int port = 443;
static int ssl_connection = LCCSCF_USE_SSL;

static lws_retry_bo_t retry = {
    .retry_ms_table = backoff_ms,
    .retry_ms_table_count = LWS_ARRAY_SIZE(backoff_ms),
    .conceal_count = LWS_ARRAY_SIZE(backoff_ms),
    .secs_since_valid_ping = 3,
    .secs_since_valid_hangup = 10,
    .jitter_percent = 20,
};

} // namespace Statics
} // namespace WebSockets

#endif
