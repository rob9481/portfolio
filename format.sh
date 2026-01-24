#!/usr/bin/env bash

clang-format -i $(find -name '*.c' -o -name '*.cpp' -o -name '*.h')
