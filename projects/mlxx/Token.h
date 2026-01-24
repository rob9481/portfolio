#ifndef TOKEN_H
#define TOKEN_H

#include <format>
#include <string>

enum class TokenType {
  // Keywords
  And,
  False,
  In,
  Let,
  Rec,
  True,

  // Literals
  LowercaseIdent,

  // Symbols
  Equal,
  Unit,

  Eof,
};

std::string toString(TokenType type);

class Token {
public:
  Token(TokenType type, std::string lexeme);

  auto toString() const -> std::string;
  auto getType() const -> TokenType { return tokenType_; }
  auto getLexeme() const -> std::string { return lexeme_; }

private:
  TokenType tokenType_;
  std::string lexeme_;
};

#endif // TOKEN_H
