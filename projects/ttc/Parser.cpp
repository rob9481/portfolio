#include "Parser.h"
#include "Token.h"
#include <iterator>

Parser::Parser(Emitter &emitter, Lexer &lexer)
    : _curToken("\0", TokenKind::Eof), _peekToken("\0", TokenKind::Eof) {
  _emitter = &emitter;
  _lexer = &lexer;

  nextToken();
  nextToken();
}

void Parser::program() {
  printf("PROGRAM\n");
  _emitter->headerLine("#include <stdio.h>");
  _emitter->headerLine("int main(void) {");

  // skip leading newlines
  while (checkToken(TokenKind::Newline)) {
    nextToken();
  }

  while (!checkToken(TokenKind::Eof)) {
    statement();
  }

  _emitter->emitLine("return 0;");
  _emitter->emitLine("}");

  for (const auto &label : _labelsGotoed) {
    if (!_labelsDeclared.contains(label)) {
      abort("Attempting to GOTO an undeclared label: " + label);
    }
  }
}

void Parser::statement() {
  if (checkToken(TokenKind::Print)) {
    printf("STATEMENT-PRINT\n");
    nextToken();
    if (checkToken(TokenKind::String)) {
      _emitter->emitLine("printf(\"" + _curToken.getText() + "\\n\");");
      nextToken();
    } else {
      _emitter->emit("printf(\"%.2f\\n\", (float)(");
      expression();
      _emitter->emitLine("));");
    }
  } else if (checkToken(TokenKind::If)) {
    printf("STATEMENT-IF\n");
    nextToken();
    _emitter->emit("if (");

    comparison();

    match(TokenKind::Then);
    nl();
    _emitter->emitLine(") {");

    while (!checkToken(TokenKind::Endif)) {
      statement();
    }
    match(TokenKind::Endif);
    _emitter->emitLine("}");
  } else if (checkToken(TokenKind::While)) {
    printf("STATEMENT-WHILE\n");
    nextToken();
    _emitter->emit("while (");

    comparison();

    match(TokenKind::Repeat);
    nl();
    _emitter->emitLine(") {");

    while (!checkToken(TokenKind::Endwhile)) {
      statement();
    }
    match(TokenKind::Endwhile);
    _emitter->emitLine("}");
  } else if (checkToken(TokenKind::Label)) {
    printf("STATEMENT-LABEL\n");
    nextToken();

    if (_labelsDeclared.contains(_curToken.getText())) {
      abort("Label already exists: " + _curToken.getText());
    }
    _labelsDeclared.insert(_curToken.getText());

    _emitter->emitLine(_curToken.getText() + ":");
    match(TokenKind::Ident);
  } else if (checkToken(TokenKind::Goto)) {
    printf("STATEMENT-GOTO\n");
    nextToken();
    _labelsGotoed.insert(_curToken.getText());
    _emitter->emitLine("goto " + _curToken.getText() + ";");
    match(TokenKind::Ident);
  } else if (checkToken(TokenKind::Let)) {
    printf("STATEMENT-LET\n");
    nextToken();

    if (!_symbols.contains(_curToken.getText())) {
      _symbols.insert(_curToken.getText());
      _emitter->headerLine("float " + _curToken.getText() + ";");
    }

    _emitter->emit(_curToken.getText() + " = ");
    match(TokenKind::Ident);
    match(TokenKind::Eq);

    expression();
    _emitter->emitLine(";");
  } else if (checkToken(TokenKind::Input)) {
    printf("STATEMENT-INPUT\n");
    nextToken();

    if (!_symbols.contains(_curToken.getText())) {
      _symbols.insert(_curToken.getText());
      _emitter->headerLine("float " + _curToken.getText() + ";");
    }
    _emitter->emitLine("if (0 == scanf(\"%f\", &" + _curToken.getText() +
                       ")) {");
    _emitter->emitLine(_curToken.getText() + " = 0;");
    _emitter->emitLine("scanf(\"%*s\");");
    _emitter->emitLine("}");
    match(TokenKind::Ident);
  } else {
    abort("Invalid statement at " + _curToken.getText() + " (" +
          tokenKindToString(_curToken.getKind()) + ")");
  }

  nl();
}

void Parser::nl() {
  printf("NEWLINE\n");
  match(TokenKind::Newline);
  while (checkToken(TokenKind::Newline)) {
    nextToken();
  }
}

bool Parser::isComparisonOperator() const {
  static const std::set<TokenKind> ops = {TokenKind::Eqeq, TokenKind::Noteq,
                                          TokenKind::Gt,   TokenKind::Gteq,
                                          TokenKind::Lt,   TokenKind::Lteq};
  return ops.contains(_curToken.getKind());
}

void Parser::comparison() {
  printf("COMPARISON\n");
  expression();

  if (isComparisonOperator()) {
    _emitter->emit(_curToken.getText());
    nextToken();
    expression();
  } else {
    abort("Expected comparison operator at: " + _curToken.getText());
  }

  while (isComparisonOperator()) {
    _emitter->emit(_curToken.getText());
    nextToken();
    expression();
  }
}

void Parser::expression() {
  printf("EXPRESSION\n");
  term();

  while (checkToken(TokenKind::Plus) || checkToken(TokenKind::Minus)) {
    _emitter->emit(_curToken.getText());
    nextToken();
    term();
  }
}

void Parser::term() {
  printf("TERM\n");
  unary();

  while (checkToken(TokenKind::Slash) || checkToken(TokenKind::Asterisk)) {
    _emitter->emit(_curToken.getText());
    nextToken();
    unary();
  }
}

void Parser::unary() {
  printf("UNARY\n");

  if (checkToken(TokenKind::Plus) || checkToken(TokenKind::Minus)) {
    _emitter->emit(_curToken.getText());
    nextToken();
  }
  primary();
}

void Parser::primary() {
  printf("PRIMARY (%s)\n", _curToken.getText().data());

  if (checkToken(TokenKind::Number)) {
    _emitter->emit(_curToken.getText());
    nextToken();
  } else if (checkToken(TokenKind::Ident)) {
    if (!_symbols.contains(_curToken.getText())) {
      abort("Referencing variable before assignment: " + _curToken.getText());
    }

    _emitter->emit(_curToken.getText());
    nextToken();
  } else {
    abort("Unexpected token at " + _curToken.getText());
  }
}

bool Parser::checkToken(TokenKind kind) const {
  return _curToken.getKind() == kind;
}

bool Parser::checkPeek(TokenKind kind) const {
  return _peekToken.getKind() == kind;
}

void Parser::match(TokenKind kind) {
  if (!checkToken(kind)) {
    abort(std::string("Expected ") + tokenKindToString(kind) + ", got " +
          tokenKindToString(_curToken.getKind()));
  }
  nextToken();
}

void Parser::nextToken() {
  _curToken = _peekToken;
  _peekToken = _lexer->getToken();
}

void Parser::abort(std::string msg) {
  printf("Parsing error: %s\n", msg.data());
  exit(1);
}
