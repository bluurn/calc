#include <sstream>
#include <string>
#include "_deps/catch2-src/extras/catch_amalgamated.hpp"
#include "token_stream.h"
#include "parser.h"

TEST_CASE("a test case for token stream") {
  std::string expr{"2+2;"};
  std::istringstream iss(expr);
  TokenStream ts(iss);
  REQUIRE( expression(ts) == 4 );
}
