#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "Lexer.h"
#include "Token.h"

class Parser {
public:
    explicit Parser(Lexer *lexer);
    auto parse() -> AST::Root *;

private:
    auto eat(TokenType type) -> void;
    auto constant() -> AST::Constant *;
    auto letBinding() -> AST::LetBinding *;
    auto valueName() -> AST::ValueName *;
    auto expr() -> AST::Expr *;

private:
    Lexer *lexer_;
    Token token_;
};

#endif // PARSER_H
