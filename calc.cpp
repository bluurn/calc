#include <iostream>
#include <stdexcept>
#include <sstream>

/*
 * Grammar:
 *
 *     Expression:
 *        Term
 *        Expression "+" Term
 *        Expression "-" Term
 *     Term:
 *        Primary
 *        Term "*" Primary
 *        Term "/" Primary
 *     Primary:
 *        Number
 *        "(" Expression ")"
 *     Number:
 *        floating-point-literal
 */

void error(const std::string& message) {
  throw std::runtime_error(message);
}

enum TokenKind {
  Number,
  Plus,
  Minus,
  Multiplication,
  Division,
  LeftParen,
  RightParen,
  Print,
  Quit,
};

class Token {
  public:
    TokenKind kind;
    double value;
    Token(char ch): kind(getTokenKind(ch)), value(0) {};
    Token(double val): kind(Number), value(val) {};

  private:
    static TokenKind getTokenKind(char c) {
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
};

class TokenStream {
  public:
    TokenStream(): full(false), buffer(0.0f) {}
    Token get() {
      if(full) {
        full = false;
        return buffer;
      }

      char ch;
      std::cin >> ch;
      switch(ch) {
        case ';':
        case 'q':
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
          return Token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          {
            std::cin.putback(ch);
            double val;
            std::cin >> val;
            return Token(val);
          }
        default:
          error("Bad token");
      }

      return Token(0.0f); // exhaustive
    }

    void putback(Token t) {
      if (full) error("putting in full buffer");
      buffer = t;
      full = true;
    }

  private:
    bool full;
    Token buffer;
};

TokenStream ts;

double term();
double primary();

/*
 * Expression:
 *    Term
 *    Expression "+" Term
 *    Expression "-" Term
 */
double expression() {
  double left = term();
  Token t = ts.get();
  while(true) {

    switch (t.kind) {
      case Plus:  
        left += term();
        t = ts.get();
        break;
      case Minus: 
        left -= term();
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
double term() {
  double left = primary();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case Multiplication:
        left *= primary();
        t = ts.get();
        break;
      case Division:
        {
          double d = primary();
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

double primary() {
  Token t = ts.get();
  switch(t.kind) {
    case LeftParen: 
      {
        double d = expression();
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

int main() {
  try {
    double val = 0.0;
    while (true) {
      Token t = ts.get();
      switch(t.kind) {
        case Quit: return 0;
        case Print: std::cout << "=" << val << std::endl; break;
        default: {
                   ts.putback(t);
                   val = expression();
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
