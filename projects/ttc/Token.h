#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <optional>
#include <string>
#include "Util.h"

#define LIST_OF_TOKEN_KINDS                                                    \
  X(Eof, -1)                                                                   \
  X(Newline, 0)                                                                \
  X(Number, 1)                                                                 \
  X(Ident, 2)                                                                  \
  X(String, 3)                                                                 \
  /* Keywords */                                                               \
  X(Label, 101)                                                                \
  X(Goto, 102)                                                                 \
  X(Print, 103)                                                                \
  X(Input, 104)                                                                \
  X(Let, 105)                                                                  \
  X(If, 106)                                                                   \
  X(Then, 107)                                                                 \
  X(Endif, 108)                                                                \
  X(While, 109)                                                                \
  X(Repeat, 110)                                                               \
  X(Endwhile, 111)                                                             \
  /* Operators */                                                              \
  X(Eq, 201)                                                                   \
  X(Plus, 202)                                                                 \
  X(Minus, 203)                                                                \
  X(Asterisk, 204)                                                             \
  X(Slash, 205)                                                                \
  X(Eqeq, 206)                                                                 \
  X(Noteq, 207)                                                                \
  X(Lt, 208)                                                                   \
  X(Lteq, 209)                                                                 \
  X(Gt, 210)                                                                   \
  X(Gteq, 211)

#define X(NAME, VALUE) NAME = VALUE,
enum class TokenKind { LIST_OF_TOKEN_KINDS };
#undef X

#define X(NAME, VALUE)                                                         \
  case TokenKind::NAME:                                                        \
    return #NAME;
inline std::string tokenKindToString(TokenKind kind) {
  switch (kind) { LIST_OF_TOKEN_KINDS };
  return "";
}
#undef X

#define X(NAME, VALUE)                                                         \
  if (toLower(#NAME) == s)                                                     \
    return TokenKind::NAME;
inline std::optional<TokenKind> stringToTokenKind(std::string s) {
  s = toLower(s);
  LIST_OF_TOKEN_KINDS;
  return {};
}
#undef X

#undef LIST_OF_TOKEN_KINDS

class Token {
public:
  Token(std::string text, TokenKind);

  TokenKind getKind() const;
  std::string getText() const;

private:
  std::string _text;
  TokenKind _kind;
};

#endif // TOKEN_H_INCLUDED
