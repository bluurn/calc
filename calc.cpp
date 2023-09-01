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
    TokenStream(std::istream& istream): is(istream), full(false), buffer(0.0f) {}
    Token get() {
      if(full) {
        full = false;
        return buffer;
      }

      char ch;
      is >> ch;
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

    void putback(Token t) {
      if (full) error("putting in full buffer");
      buffer = t;
      full = true;
    }

  private:
    std::istream& is;
    bool full;
    Token buffer;
};

double term(TokenStream& ts);
double primary(TokenStream& ts);

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

class Streamer {
  public:
    Streamer(std::istream& istr) : is(istr) {}
    void read() {
      std::string test;
      is >> test;
      std::cout << test;
    }
  private:
    std::istream& is;
};

int main() {
  
  // std::string expr { "X2+2*2-3;" };
  // std::istringstream ss(expr);
  // TokenStream ts(ss);
  // std::cout << expression(ts);
  //
  // return 0;

  TokenStream ts(std::cin);

  try {
    double val = 0.0;
    while (true) {
      Token t = ts.get();
      switch(t.kind) {
        case Quit: return 0;
        case Print: std::cout << "=" << val << std::endl; break;
        default: {
                   ts.putback(t);
                   val = expression(ts);
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
