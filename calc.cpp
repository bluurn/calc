#include <iostream>
#include "parser.h"
#include "token_stream.h"

int main() {
  
  // std::string expr { "X2+2*2-3;" };
  // std::istringstream ss(expr);
  // TokenStream ts(ss);
  // std::cout << expression(ts);
  //
  // return 0;

  TokenStream ts(std::cin);

  try {
    double val = 0.0;
    while (true) {
      Token t = ts.get();
      switch(t.kind) {
        case Quit: return 0;
        case Print: std::cout << "=" << val << std::endl; break;
        default: {
                   ts.putback(t);
                   val = expression(ts);
                 }
      }
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "unknown exception" << std::endl;
    return 2;
  }

  return 0;
}
