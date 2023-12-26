#include "vector2.hh"

#include <exception>

Vector2::Vector2() : Vector2(0, 0) {}

Vector2::Vector2(int x, int y) : x_(x), y_(y) {}

Vector2::Vector2(const Vector2& other): Vector2() {
  *this = other;
}

Vector2& Vector2::operator=(const Vector2& rhs) {
  if(this !=& rhs) {
    x_ = rhs.x_;
    y_ = rhs.y_;
  }
  return *this;
}

Vector2 Vector2::operator+(const Vector2& rhs) const {
  return Vector2(x_ + rhs.x_, y_ + rhs.y_);
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
  return Vector2(x_ - rhs.x_, y_ - rhs.y_);
}

bool Vector2::operator<(const Vector2& rhs) const {
  if (x() != rhs.x()) return x() < rhs.x();
  return y() < rhs.y();
}

bool Vector2::operator<=(const Vector2& rhs) const {
  if (x() != rhs.x()) return x() < rhs.x();
  return y() <= rhs.y();
}

bool Vector2::operator>(const Vector2& rhs) const {
  return !(*this <= rhs);
}

bool Vector2::operator>=(const Vector2& rhs) const {
  return !(*this < rhs);
}

bool Vector2::operator==(const Vector2& rhs) const {
  return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Vector2::operator!=(const Vector2& rhs) const {
  return !(*this == rhs);
}

// ### Format
// ```
//     ([x_] [y_])
// ```
// ### Ex_ample
// ```
//     (7 27)
// ```
std::ostream& operator<<(std::ostream& out, const Vector2& rhs) {
  out << '(' << rhs.x_ << " " << rhs.y_ << ')';
  return out;
}

std::istream& operator>>(std::istream& in, Vector2& rhs) {
  char dummy;
  in >> dummy >> rhs.x_ >> rhs.y_ >> dummy;
  return in;
}

bool Vector2::SerializeToOstream(std::ostream& out) const {
  out << *this;
  return true;
}

bool Vector2::ParseFromIstream(std::istream& in) {
  in >> *this;
  return true;
}