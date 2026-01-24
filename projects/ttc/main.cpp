#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include <iostream>

int main() {
  const auto input = R"(
  #PRINT "how many fib numbers?"
  #INPUT nums
  #PRINT ""
  #LET a = 0
  #LET b = 1
  #WHILE nums > 0 REPEAT
  #  PRINT a
  #  LET c = a + b
  #  LET a = b
  #  LET b = c
  #  LET nums = nums - 1
  #ENDWHILE
  LET a = 0
  WHILE a < 1 REPEAT
    PRINT "num of scores: "
    INPUT a
  ENDWHILE

  LET b = 0
  LET c = 0
  PRINT "one value at a time: "
  WHILE b < a REPEAT
    INPUT c
    LET s = s + c
    LET b = b + 1
  ENDWHILE

  PRINT "Average: "
  PRINT s / a
  )";

  printf("Teeny Tiny Compiler\n");
  auto lexer = Lexer(input);
  auto emitter = Emitter();
  auto parser = Parser(emitter, lexer);
  parser.program();
  emitter.writeFile("out.c");
  printf("Parsing completed.\n");

  return 0;
}
