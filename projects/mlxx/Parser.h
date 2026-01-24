#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include "AST.h"
#include "Lexer.h"
#include "Token.h"

class Parser {
public:
    explicit Parser(Lexer* lexer);
    auto parse() -> std::unique_ptr<AST::Root>;

private:
    auto eat(TokenType type) -> void;
    auto constant() -> std::unique_ptr<AST::Constant>;
    auto letBinding() -> std::unique_ptr<AST::LetBinding>;
    auto valueName() -> std::unique_ptr<AST::ValueName>;
    auto expr() -> std::unique_ptr<AST::Expr>;

private:
    Lexer *lexer_;
    Token token_;
};

#endif // PARSER_H
