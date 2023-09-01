#pragma once
#include <istream>
#include "token.hpp"

class TokenStream {
  public:
    TokenStream(std::istream& istream);
    Token get();

    void putback(Token t);

  private:
    std::istream& is;
    bool full;
    Token buffer;
};
