#include "../include/Vector2.h"

Vector2::Vector2() : Vector2(0, 0) {}
Vector2::Vector2(int x, int y) : x(x), y(y) {}

int Vector2::getX() const {
    return x;
}
int Vector2::getY() const {
    return y;
}

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