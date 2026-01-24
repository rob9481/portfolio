#ifndef LEXER_H
#define LEXER_H

#include <unordered_map>
#include "Token.h"

class Lexer {
public:
    explicit Lexer(std::string text);
    auto getNextToken() -> Token;

private:
    auto advance() -> std::optional<char>;
    auto match(char ch) -> bool;
    auto symbol() -> std::optional<Token>;
    auto lowercaseIdent() -> std::optional<Token>;
    auto skipSpace() -> void;

private:
    std::string text_;
    int pos_;
    std::optional<char> char_;
    std::unordered_map<std::string, TokenType> keywords_;
    std::unordered_map<std::string, TokenType> symbols_;
};

#endif // LEXER_H
