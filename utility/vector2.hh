#ifndef CONWAY_INCLUDE_VECTOR2_HPP
#define CONWAY_INCLUDE_VECTOR2_HPP

#include <iostream>
#include <utility>

#include "utility/vector2.pb.h"

/// 2D vector for positional coordinates (immutable)
class Vector2 {
 public:
  /// create (0,0) vector
  Vector2();

  /// create (x,y) vector
  Vector2(int x, int y);

  Vector2(const Vector2& other);
  Vector2& operator= (const Vector2& rhs);

  Vector2 operator+(const Vector2& rhs) const;
  Vector2 operator-(const Vector2& rhs) const;
  // Vector2& operator+=(const Vector2& rhs);
  // Vector2& operator-=(const Vector2& rhs);
  bool operator<(const Vector2& rhs) const;
  bool operator<=(const Vector2& rhs) const;
  bool operator>=(const Vector2& rhs) const;
  bool operator>(const Vector2& rhs) const;
  bool operator==(const Vector2& rhs) const;
  bool operator!=(const Vector2& rhs) const;

  friend std::ostream& operator<<(std::ostream& out, const Vector2& rhs);
  friend std::istream& operator>>(std::istream& in, Vector2& rhs);
  bool SerializeToOstream(std::ostream& out) const;
  bool ParseFromIstream(std::istream& in);

  conway::Vector2& CopyToProtobuf(conway::Vector2& pb) const;

  // structured bindings -- https://devblogs.microsoft.com/oldnewthing/20201015-00/?p=104369
  template<std::size_t Index>
  std::tuple_element_t<Index, Vector2> get() const {
    if constexpr (Index == 0) return x();
    if constexpr (Index == 1) return y();
  }

  // getters & setters for embind
  int x() const { return x_; }
  int y() const { return y_; }
  void set_x(int x) { x_ = x; }
  void set_y(int y) { y_ = y; }

 private:
  int x_ = 0;
  int y_ = 0;
};

// https://www.albertogramaglia.com/modern-cpp-structured-binding/
namespace std {
  template<>
  struct tuple_size<Vector2>
  : std::integral_constant<std::size_t, 2> { };

  template<>
  struct tuple_element<0, Vector2> {
    using type = int;
  };
  template<>
  struct tuple_element<1, Vector2> {
    using type = int;
  };
}

#endif // CONWAY_INCLUDE_VECTOR2_HPP