#pragma once
#include <istream>
#include "token.h"

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
