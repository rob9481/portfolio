#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include "Token.h"
#include <optional>
#include <string>

class Lexer final {
public:
  explicit Lexer(std::string);

  Token getToken();

private:
  char peek() const;

  void skipWhitespace();
  void skipComment();

  void abort(std::string msg);
  void nextChar();

  std::string _source;
  char _curChar;
  std::string::size_type _curPos;
};

#endif // LEXER_H_INCLUDED
