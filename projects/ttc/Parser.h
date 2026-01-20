#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <set>
#include "Emitter.h"
#include "Lexer.h"

/*
 * Grammar
 * -------
 *
 * program ::= {statement}
 *
 * statement ::= "PRINT" (expression | string) nl
 *             | "IF" comparison "THEN" nl {statement} "ENDIF" nl
 *             | "WHILE" comparison "REPEAT" nl {statement} "ENDWHILE" nl
 *             | "LABEL" ident nl
 *             | "GOTO" ident nl
 *             | "LET" ident "=" expression nl
 *             | "INPUT" ident nl
 *
 * comparison ::= expression (("==") | "!=" | ">" | ">=" | "<" | "<=")
 *expression)+
 *
 * expression ::= term {( "-" | "+") term}
 *
 * term ::= unary {( "/" | "*") unary}
 *
 * unary ::= ["+" | "-"] primary
 *
 * primary ::= number | ident
 *
 * nl ::= '\n'+
 *
 * ---
 * {}: zero or more
 * []: zero or one
 * + : one or more
 * (): for grouping
 * | : logical or
 * "": keywords and operators
 * words: references to rules or to tokens defined in the lexer
 **/

class Parser {
public:
  explicit Parser(Emitter &, Lexer &);

  void program();

private:
  // rules
  void statement();
  void comparison();
  void expression();
  void term();
  void unary();
  void primary();
  void nl();

  // parsing primitives
  bool checkToken(TokenKind) const;
  bool checkPeek(TokenKind) const;
  void match(TokenKind);
  void nextToken();
  void abort(std::string msg);

  // helpers
  bool isComparisonOperator() const;

  // variables
  Emitter *_emitter;
  Lexer *_lexer;
  std::set<std::string> _symbols, _labelsDeclared, _labelsGotoed;
  Token _curToken, _peekToken;
};

#endif // PARSER_H_INCLUDED
