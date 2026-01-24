#include "Parser.h"
#include <format>

using namespace AST;

Parser::Parser(Lexer *lexer) : token_(TokenType::Eof, "") {
  lexer_ = lexer;
  token_ = lexer->getNextToken();
}

auto Parser::parse() -> std::unique_ptr<AST::Root> { return expr(); }

auto Parser::eat(TokenType type) -> void {
  if (token_.getType() == type)
    token_ = lexer_->getNextToken();
  else {
    throw std::runtime_error(std::format("Parser: expected ({}), got ({})",
                                         toString(type),
                                         toString(token_.getType())));
  }
}

auto Parser::constant() -> std::unique_ptr<AST::Constant> {
  switch (token_.getType()) {
  case TokenType::False:
  case TokenType::True:
  case TokenType::Unit:
    const auto type = token_.getType();
    eat(type);
    return std::make_unique<Constant>(type);
  }

  return {};
}

auto Parser::letBinding() -> std::unique_ptr<AST::LetBinding> {
  auto valueName1 = valueName();
  eat(TokenType::Equal);
  auto expr1 = expr();
  return std::make_unique<LetBinding>(std::move(valueName1), std::move(expr1));
}

auto Parser::valueName() -> std::unique_ptr<AST::ValueName> {
  const auto token = token_;
  eat(TokenType::LowercaseIdent);
  return std::make_unique<ValueName>(token);
}

auto Parser::expr() -> std::unique_ptr<AST::Expr> {
  auto constant1 = constant();
  if (constant1)
    return std::make_unique<ExprConstant>(std::move(constant1));

  eat(TokenType::Let);
  auto rec = false;
  if (token_.getType() == TokenType::Rec) {
    eat(TokenType::Rec);
    rec = true;
  }

  auto letBinding1 = letBinding();
  eat(TokenType::In);
  auto expr1 = expr();
  return std::make_unique<ExprLet>(rec, std::move(letBinding1),
                                   std::move(expr1));
}
