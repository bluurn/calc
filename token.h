#pragma once
#include "token_kind.h"

class Token {
  public:
    TokenKind kind;
    double value;
    Token(char ch);
    Token(double val);
};
