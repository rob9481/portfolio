cmake_minimum_required(VERSION 3.10)
project(breakneck)

set(CMAKE_CXX_STANDARD 20)

add_executable(breakneck
  Elevator.cpp
  Elevator.h
  ElevatorBankPanel.cpp
  ElevatorBankPanel.h
  ElevatorScheduler.cpp
  ElevatorScheduler.h
  main.cxx
)
