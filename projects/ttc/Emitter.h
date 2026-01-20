#ifndef EMITTER_H_INCLUDED
#define EMITTER_H_INCLUDED

#include <string>

class Emitter {
public:
  void emit(std::string);
  void emitLine(std::string);
  void headerLine(std::string);

  void writeFile(std::string path);

private:
  std::string _header, _source;
};

#endif // EMITTER_H_INCLUDED
