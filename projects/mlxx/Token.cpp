#include "Token.h"

std::string toString(TokenType type) {
  switch (type) {
    using enum TokenType;
  case And:
    return "And";
  case False:
    return "False";
  case In:
    return "In";
  case Let:
    return "Let";
  case Rec:
    return "Rec";
  case True:
    return "True";
  case LowercaseIdent:
    return "LowercaseIdent";
  case Equal:
    return "Equal";
  case Unit:
    return "Unit";
  case Eof:
    return "Eof";
  }
  return {};
}

Token::Token(TokenType type, std::string lexeme) {
  tokenType_ = type;
  lexeme_ = lexeme;
}

auto Token::toString() const -> std::string {
  return std::format("Token({}, {})", ::toString(tokenType_), lexeme_);
}
