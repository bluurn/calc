#include "token_kind.h"

TokenKind getTokenKind(char c) {
  switch (c) {
    case '+': return Plus;
    case '-': return Minus;
    case '*': return Multiplication;
    case '/': return Division;
    case '(': return LeftParen;
    case ')': return RightParen;
    case ';': return Print;
    case 'q': return Quit;
    default:  return Number;
  }
}

