#include "../include/vicpad/unint.h"

namespace utils {
  unint::unint() : i(0){}
   
  unint::unint(int64_t n) {
    i = (n < 0) ? 0 : n;
  }
  
  unint::unint(const unint& n) : i(n.i){}
  
  unint& unint::operator--() {
    if (i) i--;
    return *this;
  }
  
  unint unint::operator--(int) {
    unint copy(*this);
    if (i) i--;
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
  
  // unint unint::operator+(const unint& n) const {
  //   return unint(i + n.i);
  // }
  
  // unint unint::operator-(const unint& n) const {
  //   return unint(i - n.i);
  // }
  
  // unint::operator int() const {
  //   return i;
  // }
  
  unint::operator uint64_t() const {
    return i;
  }
  
  uint64_t unint::value() const {
    return i;
  }
}