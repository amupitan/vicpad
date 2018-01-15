#include "../include/vicpad/unint.h"

namespace utils {
  unint::unint(int64_t n) {
    i = (n < 0) ? 0 : n;
  }
  
  unint::unint(const unint& n) : i(n.i){}
  
  unint& unint::operator--() {
    i--;
    return *this;
  }
  
  unint unint::operator--(int) {
    unint copy(*this);
    i--;
    return copy;
  }
  
  unint& unint::operator++() {
    i++;
    return *this;
  }
  
  unint unint::operator++(int) {
    unint copy(*this);
    i++;
    return copy;
  }
  
  unint unint::operator+(const unint& n) const {
    return unint(i + n.i);
  }
  
  unint unint::operator-(const unint& n) const {
    return unint(i - n.i);
  }
  
  uint64_t unint::value() const {
    return i;
  }
}