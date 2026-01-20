#include "Util.h"

std::string toLower(std::string s) {
  for (auto &ch : s) {
    ch = tolower(ch);
  }
  return s;
}
