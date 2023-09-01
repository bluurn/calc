#include "error.h"
#include <stdexcept>

void error(const std::string& message) {
  throw std::runtime_error(message);
}
