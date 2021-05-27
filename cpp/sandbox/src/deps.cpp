#ifndef DEPENDENCIES
#define DEPENDENCIES

#ifndef DEPENDENCY__LIBWEBSOCKETS
#define DEPENDENCY__LIBWEBSOCKETS
#include <libwebsockets.h>
#endif

#ifndef DEPENDENCY__NLOHMANN__JSON
#define DEPENDENCY__NLOHMANN__JSON
#include "deps/nlohmann/json.hpp" // nlohmann::json
using json = nlohmann::json;
#endif

#endif
