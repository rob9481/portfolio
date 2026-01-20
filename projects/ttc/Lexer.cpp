#include <cctype>
#include <iostream>
#include <iterator>
#include <set>
#include "Lexer.h"
#include "Token.h"

Lexer::Lexer(std::string source) {
  _source = source + '\n';
  _curChar = '\n';
  _curPos = -1;
  nextChar();
}

Token Lexer::getToken() {
  skipWhitespace();
  skipComment();
  std::optional<Token> token;

  auto str = [](char ch) { return std::string(1, ch); };

  if (_curChar == '+') {
    token = Token(str(_curChar), TokenKind::Plus);
  } else if (_curChar == '-') {
    token = Token(str(_curChar), TokenKind::Minus);
  } else if (_curChar == '*') {
    token = Token(str(_curChar), TokenKind::Asterisk);
  } else if (_curChar == '/') {
    token = Token(str(_curChar), TokenKind::Slash);
  } else if (_curChar == '\n') {
    token = Token(str(_curChar), TokenKind::Newline);
  } else if (_curChar == '\0') {
    token = Token(str(_curChar), TokenKind::Eof);
  } else if (_curChar == '=') {
    if (peek() == '=') {
      auto prevChar = _curChar;
      nextChar();
      token = Token(str(prevChar) + str(_curChar), TokenKind::Eqeq);
    } else {
      token = Token(str(_curChar), TokenKind::Eq);
    }
  } else if (_curChar == '>') {
    if (peek() == '=') {
      auto prevChar = _curChar;
      nextChar();
      token = Token(str(prevChar) + _curChar, TokenKind::Gteq);
    } else {
      token = Token(str(_curChar), TokenKind::Gt);
    }
  } else if (_curChar == '<') {
    if (peek() == '=') {
      auto prevChar = _curChar;
      nextChar();
      token = Token(str(prevChar) + str(_curChar), TokenKind::Lteq);
    } else {
      token = Token(str(_curChar), TokenKind::Lt);
    }
  } else if (_curChar == '!') {
    if (peek() == '=') {
      auto prevChar = _curChar;
      nextChar();
      token = Token(str(prevChar) + str(_curChar), TokenKind::Noteq);
    } else {
      abort("Expected !=, got !" + str(peek()));
    }
  } else if (_curChar == '"') {
    nextChar();
    const auto startPos = _curPos;
    while (_curChar != '"') {
      static std::set<char> illegalChars = {'\r', '\n', '\t', '\\', '%'};
      if (illegalChars.contains(_curChar)) {
        abort("Illegal character in string: " + str(_curChar));
      }
      nextChar();
    }
    const auto text =
        std::string(_source.begin() + startPos, _source.begin() + _curPos);
    token = Token(text, TokenKind::String);

  } else if (isdigit(_curChar)) {
    const auto startPos = _curPos;
    while (isdigit(peek())) {
      nextChar();
    }
    if (peek() == '.') {
      nextChar();
      if (!isdigit(peek())) {
        abort("Illegal character in number.");
      }
      while (isdigit(peek())) {
        nextChar();
      }
    }
    const auto text =
        std::string(_source.begin() + startPos, _source.begin() + _curPos + 1);
    token = Token(text, TokenKind::Number);
  } else if (isalpha(_curChar)) {
    const auto startPos = _curPos;
    while (std::isalnum(peek())) {
      nextChar();
    }
    const auto text = _source.substr(startPos, _curPos + 1 - startPos);
    const auto kind = stringToTokenKind(text);
    if (kind) {
      token = Token(text, *kind);
    } else {
      token = Token(text, TokenKind::Ident);
    }
  } else {
    abort(std::string("Unknown token <") + _curChar + ">");
  }

  nextChar();
  return *token;
}

char Lexer::peek() const {
  if (_curPos + 1 >= _source.size()) {
    return '\0';
  }
  return _source[_curPos + 1];
}

void Lexer::skipComment() {
  if (_curChar == '#') {
    while (_curChar != '\n') {
      nextChar();
    }
  }
}

void Lexer::skipWhitespace() {
  while (_curChar == ' ' || _curChar == '\t' || _curChar == '\r')
    nextChar();
}

void Lexer::abort(std::string msg) {
  printf("Lexing error: %s\n", msg.data());
  exit(1);
}

void Lexer::nextChar() {
  _curPos += 1;
  if (_curPos >= _source.size())
    _curChar = '\0';
  else
    _curChar = _source[_curPos];
}
