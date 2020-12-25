#if !defined CURL_CLIENT_H
#define CURL_CLIENT_H

#include "lib/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <curl/curl.h> // CURL, curl_easy_init (package: libcurl4-openssl-dev)
#include <map>         // std::map
#include <string>      // std::string

class CurlClient {
public:
  enum debug_t { OFF, ON };
  enum http_method_t { GET, POST, PUT };

  struct props_t {
    std::string body;
    std::map<std::string, std::string> body_params;
    debug_t debug_flag;
    std::map<std::string, std::string> headers;
    http_method_t method;
    std::map<std::string, std::string> query_params;
    std::string url;
  };

  struct response_t {
    std::string body;
    std::map<std::string, std::string> headers;
    size_t size;
  } response;

  CurlClient(CurlClient::props_t);

  static std::string method_to_string(http_method_t);

  bool is_xml_response();
  void log_request();
  void request();

private:
  struct transformed_props_t {
    std::string body;
    std::string headers;
    std::string method;
    std::string query_params;
    std::string url;
  } transformed_props;

  CURL *curl = curl_easy_init();

  CurlClient::props_t props = {
      .body = "",
      .body_params = {},
      .debug_flag = debug_t::OFF,
  };

  Formatted::fmt_stream_t stream_format = Formatted::stream();
  std::string build_query_params();
  std::string to_string();

  static constexpr const char *HTTP_METHODS[3] = {"GET", "POST", "PUT"};
  static size_t write_response_body(char *, size_t, size_t, void *);
  static size_t write_response_headers(char *, size_t, size_t, void *);

  void prepare_request();
  void set_request_body();
  void set_debug();
  void set_headers();
  void set_method();
  void set_url();
};
#endif