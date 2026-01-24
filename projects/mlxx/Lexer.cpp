#include "Lexer.h"

Lexer::Lexer(std::string text) {
  text_ = text;
  pos_ = 0;
  char_ = text.front();

  keywords_ = {
      {"and", TokenType::And},   {"false", TokenType::False},
      {"in", TokenType::In},     {"let", TokenType::Let},
      {"rec", TokenType::Rec},   {"true", TokenType::True},
      {"unit", TokenType::Unit},
  };

  symbols_ = {
      {"=", TokenType::Equal},
  };
}

auto Lexer::getNextToken() -> Token {
  while (char_) {
    if (std::isspace(*char_)) {
      skipSpace();
      if (!*char_)
        break;
    }

    auto tokenOpt = symbol();
    if (tokenOpt)
      return *tokenOpt;

    tokenOpt = lowercaseIdent();
    if (tokenOpt)
      return *tokenOpt;

    throw std::runtime_error("Lexer: invalid");
  }

  return Token(TokenType::Eof, "");
}

auto Lexer::advance() -> std::optional<char> {
  pos_ += 1;

  if (pos_ >= text_.size())
    char_.reset();
  else
    char_ = text_[pos_];

  return char_;
}

auto Lexer::match(char ch) -> bool {
  if (pos_ < text_.size() && *char_ == ch) {
    advance();
    return true;
  }
  return false;
}

auto Lexer::symbol() -> std::optional<Token> {
  if (*char_ == '(') {
    advance();
    if (match(')'))
      return Token(TokenType::Unit, "()");
  }

  const std::string lexeme{*char_};
  if (symbols_.contains(lexeme)) {
    // TODO assert
    const auto type = symbols_[lexeme];
    advance();
    return Token(type, lexeme);
  }

  return {};
}

auto Lexer::lowercaseIdent() -> std::optional<Token> {
  const auto start = pos_;
  auto ch = char_;
  if (ch && (std::islower(*ch) || *ch == '_'))
    ch = advance();
  else
    return {};

  while (ch && (std::isalnum(*ch) || *ch == '_' || *ch == '\''))
    ch = advance();

  const auto lexeme = text_.substr(start, pos_ - start);
  TokenType type = TokenType::LowercaseIdent;
  if (keywords_.contains(lexeme))
    type = keywords_[lexeme];

  return Token(type, lexeme);
}

auto Lexer::skipSpace() -> void {
  while (char_ && std::isspace(*char_))
    advance();
}
