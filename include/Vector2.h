#ifndef CW_VECTOR2_H
#define CW_VECTOR2_H

#include <iostream>

/// 2D vector for positional coordinates (immutable)
class Vector2 {
    private:
        int x, y;
    public:
        /// create (0,0) vector
        Vector2();

        /// create (x,y) vector
        Vector2(int x, int y);

        /// @return x value of the coordinate
        int getX() const;

        /// @return y value of the coordinate
        int getY() const;

        Vector2 operator+(const Vector2& rhs) const;
        Vector2 operator-(const Vector2& rhs) const;
        friend std::ostream& operator<<(std::ostream &out, const Vector2 &rhs);
};

#endif