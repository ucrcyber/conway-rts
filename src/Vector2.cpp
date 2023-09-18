#include "Vector2.hpp"

#include <exception>

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(int x, int y) : _x(x), _y(y) {}

Vector2& Vector2::operator=(const Vector2& rhs) {
  _x = rhs.x;
  _y = rhs.y;
  return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs) const {
  return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
  return Vector2(x - rhs.x, y - rhs.y);
}

bool Vector2::operator==(const Vector2& rhs) const {
  return x == rhs.x && y == rhs.y;
}

bool Vector2::operator!=(const Vector2& rhs) const {
  return !(*this == rhs);
}

// ### Format
// ```
//     ([x] [y])
// ```
// ### Example
// ```
//     (7 27)
// ```
std::ostream& operator<<(std::ostream &out, const Vector2 &rhs) {
  out << '(' << rhs.x << " " << rhs.y << ')';
  return out;
}

std::istream& operator>>(std::istream &in, Vector2 &rhs) {
  char dummy;
  in >> dummy >> rhs._x >> rhs._y >> dummy;
  return in;
}

bool Vector2::SerializeToOstream(std::ostream &out) const {
  out << *this;
  return true;
}

bool Vector2::ParseFromIstream(std::istream &in) {
  in >> *this;
  return true;
}