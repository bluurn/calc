#include "token.hpp"
#include "token_kind.hpp"

Token::Token(double val): kind(Number), value(val) {};

Token::Token(char ch): value(0) {
  this->kind = getTokenKind(ch);
};


