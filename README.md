# Portfolio

## Exercises

- [EvenPalindromes](exercises/EvenPalindromes.cpp): Quickly written implementation for finding all even 8-digit palindromes.
  - https://interviewing.io/mocks/spotify-java-even-palindrome-generator
- Newton's method for square root in [C++](exercises/newton.cpp) and [Python](exercises/newton.py)
- [SleepySort](exercises/SleepySort.cpp): Sort by the amount of time a thread sleeps.

## Projects

- [Breakneck](projects/breakneck): A silly little multithreaded elevator simulator
- [MLxx](projects/mlxx): An exceedingly small subset of the OCaml frontend in C++
  - `cmake -B build -S projects/mlxx && cmake --build build && ./build/mlxx`
  - Ref: <https://craftinginterpreters.com/>
  - Ref: <https://ruslanspivak.com/lsbasi-part1/>

## Tutorials
- [Ray Tracing in One Weekend](projects/rtow)
  - `cmake -B build -S projects/rtow && cmake --build build && ./build/rtow > image.ppm`
  - Based on <https://raytracing.github.io/books/RayTracingInOneWeekend.html>
- [Teeny Tiny Compiler](src/ttc)
  - `cmake -B build -S projects/ttc && cmake --build build && ./build/ttc && gcc out.c && ./a.out`
  - Based on <https://austinhenley.com/blog/teenytinycompiler1.html>
