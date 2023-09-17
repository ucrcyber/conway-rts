#ifndef CONWAY_VECTOR2_HPP
#define CONWAY_VECTOR2_HPP

#include "ISerializable.hpp"

/// 2D vector for positional coordinates (immutable)
class Vector2: public ISerializable<Vector2> {
  private:
    int _x = 0;
    int _y = 0;
  public:
    // https://stackoverflow.com/a/5424521/21507383 public readonly, private variables

    /// @brief readonly x value
    const int& x = _x;

    /// @brief readonly y value
    const int& y = _y;

    /// create (0,0) vector
    Vector2();

    /// create (x,y) vector
    Vector2(int x, int y);

    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    // Vector2& operator+=(const Vector2& rhs);
    // Vector2& operator-=(const Vector2& rhs);
};

#endif