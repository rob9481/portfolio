cmake_minimum_required(VERSION 3.10)
project(mlxx)

set(CMAKE_CXX_STANDARD 20)

add_executable(mlxx
  AST.cpp
  AST.h
  Lexer.cpp
  Lexer.h
  Parser.cpp
  Parser.h
  Token.cpp
  Token.h
  main.cpp
)
