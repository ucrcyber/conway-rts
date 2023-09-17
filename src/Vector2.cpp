#include "../include/Vector2.hpp"
#include <exception>

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(int x, int y) : _x(x), _y(y) {}

Vector2 Vector2::operator+(const Vector2& rhs) const {
  return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
  return Vector2(x - rhs.x, y - rhs.y);
}

std::ostream& operator<<(std::ostream &out, const Vector2 &rhs){
  out << '(' << rhs.x << ", " << rhs.y << ')';
  return out;
}

std::istream& operator>>(std::istream &in, const Vector2 &rhs){
  // not implemented (is this useful?)
  return in;
}