cmake_minimum_required(VERSION 3.10)
project(ttc)

set(CMAKE_CXX_STANDARD 20)

add_executable(ttc
  Emitter.h
  Emitter.cpp
  Lexer.h
  Lexer.cpp
  Parser.h
  Parser.cpp
  Token.h
  Token.cpp
  Util.h
  Util.cpp
  main.cpp)
