#include <sstream>
#include "token_stream.hpp"
#include "error.hpp"


TokenStream::TokenStream(std::istream& istream): is(istream), full(false), buffer(0.0f) {}
Token TokenStream::get() {
      if(full) {
        full = false;
        return buffer;
      }

      char ch;
      is >> ch;
      switch(ch) {
        case ';': case 'q': case '(': case ')': case '+': case '-': case '*': case '/':
          return Token(ch);
        case '.': case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
          {
            is.putback(ch);
            double val;
            is >> val;
            return Token(val);
          }
        default:
          {
            std::stringstream errstr;
            errstr << "Bad token: " << ch;
            error(errstr.str());
          }
      }

      return Token(0.0f); // exhaustive
}

void TokenStream::putback(Token t) {
  if (full) error("putting in full buffer");
  buffer = t;
  full = true;
}
