#include "Emitter.h"

void Emitter::emit(std::string s) { _source += s; }

void Emitter::emitLine(std::string s) {
  emit(s);
  _source += '\n';
}

void Emitter::headerLine(std::string s) { _header += s + '\n'; }

void Emitter::writeFile(std::string path) {
  FILE *file = fopen(path.c_str(), "wt");
  fprintf(file, "%s", (_header + _source).c_str());
  fclose(file);
}
