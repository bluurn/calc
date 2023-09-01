#include "token.h"
#include "token_kind.h"

Token::Token(double val): kind(Number), value(val) {};

Token::Token(char ch): value(0) {
  this->kind = getTokenKind(ch);
};


