#ifndef CONWAY_INCLUDE_VECTOR2_HPP
#define CONWAY_INCLUDE_VECTOR2_HPP

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

    Vector2(const Vector2& other);
    Vector2& operator= (const Vector2& rhs);

    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    // Vector2& operator+=(const Vector2& rhs);
    // Vector2& operator-=(const Vector2& rhs);
    bool operator==(const Vector2& rhs) const;
    bool operator!=(const Vector2& rhs) const;

    friend std::ostream& operator<<(std::ostream &out, const Vector2 &rhs);
    friend std::istream& operator>>(std::istream &in, Vector2 &rhs);
    bool SerializeToOstream(std::ostream &out) const;
    bool ParseFromIstream(std::istream &in);
};

#endif // CONWAY_INCLUDE_VECTOR2_HPP