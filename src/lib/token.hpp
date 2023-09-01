#pragma once
#include "token_kind.hpp"

class Token {
  public:
    TokenKind kind;
    double value;
    Token(char ch);
    Token(double val);
};
