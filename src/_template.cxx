// main include (Ctrl+H replace CLASSNAME with whatever the class name is)
#include "CLASSNAME.hpp"

// stl includes

// lib includes

// other includes

// method implementations

CLASSNAME::CLASSNAME(const CLASSNAME& other): CLASSNAME() {
  *this = other;
}

CLASSNAME& CLASSNAME::operator=(const CLASSNAME& other) {
  if(this != &other) {
    grid = other.grid;
  }
  return *this;
}

bool CLASSNAME::operator==(const CLASSNAME& other) const {
  if(this == &other) return true;
  
  return true;
}

bool CLASSNAME::operator!=(const CLASSNAME& other) const {
  return !(*this == other);
}

// ### Format
// ```
//     AAAAAAA
// ```
// ### Example
// ```
//     AAAAAAA
// ```
std::ostream& operator<<(std::ostream& out, const CLASSNAME& rhs) {
  out << '(' << rhs.x << " " << rhs.y << ')';
  return out;
}

std::istream& operator>>(std::istream& in, CLASSNAME& rhs) {
  char dummy;
  in >> dummy >> rhs._x >> rhs._y >> dummy;
  return in;
}

bool CLASSNAME::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool CLASSNAME::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}