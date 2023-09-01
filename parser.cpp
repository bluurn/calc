#include "parser.h"
#include "error.h"

/*
 * Expression:
 *    Term
 *    Expression "+" Term
 *    Expression "-" Term
 */
double expression(TokenStream& ts) {
  double left = term(ts);
  Token t = ts.get();
  while(true) {

    switch (t.kind) {
      case Plus:  
        left += term(ts);
        t = ts.get();
        break;
      case Minus: 
        left -= term(ts);
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }
}

/*
 * Term:
 *    Primary
 *    Term "*" Primary
 *    Term "/" Primary
 */
double term(TokenStream& ts) {
  double left = primary(ts);
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case Multiplication:
        left *= primary(ts);
        t = ts.get();
        break;
      case Division:
        {
          double d = primary(ts);
          if(d == 0) error("division by zero");
          left /= d;
          t = ts.get();
          break;
        }
      default: 
        ts.putback(t);
        return left;
    }
  }
}

/*
 * Primary:
 *    Number
 *    "(" Expression ")"
 */

double primary(TokenStream& ts) {
  Token t = ts.get();
  switch(t.kind) {
    case LeftParen: 
      {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != RightParen) error("')' expected");
        return d;
      }
    case Number:
      return t.value;
    default:
      error("primary expected");
  }
  return 0; // exhaustive 
}
