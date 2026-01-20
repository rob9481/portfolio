#include "Token.h"

Token::Token(std::string text, TokenKind kind) {
  _text = text;
  _kind = kind;
}

TokenKind Token::getKind() const { return _kind; }

std::string Token::getText() const { return _text; }
