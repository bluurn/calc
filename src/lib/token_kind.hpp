#pragma once

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

TokenKind getTokenKind(char c);
