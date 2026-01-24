#include <format>
#include "Parser.h"

using namespace AST;

Parser::Parser(Lexer* lexer) : token_(TokenType::Eof, "") {
    lexer_ = lexer;
    token_ = lexer->getNextToken();
}

auto Parser::parse() -> AST::Root * {
    return expr();
}

auto Parser::eat(TokenType type) -> void {
    if (token_.getType() == type)
        token_ = lexer_->getNextToken();
    else {
        throw std::runtime_error(std::format("Parser: expected ({}), got ({})",
                                             toString(type),
                                             toString(token_.getType())));
    }
}

auto Parser::constant() -> AST::Constant * {
    switch (token_.getType()) {
        case TokenType::False:
        case TokenType::True:
        case TokenType::Unit:
            const auto type = token_.getType();
            eat(type);
            return new Constant(type);
    }

    return {};
}

auto Parser::letBinding() -> AST::LetBinding * {
    auto *valueName1 = valueName();
    eat(TokenType::Equal);
    auto *expr1 = expr();
    return new LetBinding(valueName1, expr1);
}

auto Parser::valueName() -> AST::ValueName * {
    const auto token = token_;
    eat(TokenType::LowercaseIdent);
    return new ValueName(token);
}

auto Parser::expr() -> AST::Expr * {
    auto *constant1 = constant();
    if (constant1)
        return new ExprConstant(constant1);

    eat(TokenType::Let);
    auto rec = false;
    if (token_.getType() == TokenType::Rec) {
        eat(TokenType::Rec);
        rec = true;
    }

    auto *letBinding1 = letBinding();
    eat(TokenType::In);
    auto *expr1 = expr();
    return new ExprLet(rec, letBinding1, expr1);
}
