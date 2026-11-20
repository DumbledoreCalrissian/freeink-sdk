#pragma once

#include <string>
#include "Arduino.h"

namespace fakeString {
inline bool reserveFails = false;
}

class String : public std::string {
 public:
  using std::string::string;
  String(const std::string& value) : std::string(value) {}
  // Arduino returns 0 when the allocation fails.
  unsigned char reserve(unsigned int size) {
    if (fakeString::reserveFails) return 0;
    std::string::reserve(size);
    return 1;
  }
  bool concat(const char* text, unsigned int length) {
    append(text, length);
    return true;
  }
  bool endsWith(const char* suffix) const {
    const size_t count = std::char_traits<char>::length(suffix);
    return size() >= count && compare(size() - count, count, suffix) == 0;
  }
};
