#include "Structure.hpp"

// stl includes

// lib includes

// other includes

// method implementations

// ### Format
// ```
//     AAAAAAA
// ```
// ### Example
// ```
//     AAAAAAA
// ```
std::ostream& operator<<(std::ostream &out, const Structure &rhs) {
  return out;
}

std::istream& operator>>(std::istream &in, Structure &rhs) {
  return in;
}

bool Structure::SerializeToOstream(std::ostream &out) const {
  out << *this;
  return true;
}

bool Structure::ParseFromIstream(std::istream &in) {
  in >> *this;
  return true;
}