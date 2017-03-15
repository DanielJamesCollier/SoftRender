// my
#include "Vec2.hpp"

namespace Maths {

//------------------------------------------------------------
Vec2::Vec2(float _x, float _y) :
    x(_x)
,   y(_y)
{
    // empty
}

//------------------------------------------------------------
float 
Vec2::length() const {
    return std::sqrt(x * x + y * y);
}

//------------------------------------------------------------
float
Vec2::length2() const {
    return x * x + y * y;
}

//------------------------------------------------------------
void 
Vec2::normalise() {
    float len = length();
    x /= len;
    y /= len;
}

//------------------------------------------------------------
float 
Vec2::dot(Vec2 const & vec) const {
    return x * vec.x + y * vec.y;
}

//------------------------------------------------------------
Vec2
Vec2::operator + () const {
    return *this;
}

//------------------------------------------------------------
Vec2 
Vec2::operator - () const {
    return Vec2(-x, -y);
}

//------------------------------------------------------------
Vec2
Vec2::operator + (Vec2 const & vec) {
    return Vec2(x + vec.x, y + vec.y);
}

//------------------------------------------------------------
Vec2
Vec2::operator - (Vec2 const & vec) {
    return Vec2(x - vec.x, y - vec.y);
}

//------------------------------------------------------------
Vec2
Vec2::operator * (Vec2 const & vec) {
    return Vec2(x * vec.x, y * vec.y);
}

//------------------------------------------------------------
Vec2
Vec2::operator / (Vec2 const & vec) {
    return Vec2(x / vec.x, y / vec.y);
}

//------------------------------------------------------------
Vec2
Vec2::operator + (float scalar) {
    return Vec2(x + scalar, y + scalar);
}

//------------------------------------------------------------
Vec2
Vec2::operator - (float scalar) {
    return Vec2(x - scalar, y - scalar);
}

//------------------------------------------------------------
Vec2
Vec2::operator * (float scalar) {
    return Vec2(x * scalar, y * scalar);
}

//------------------------------------------------------------
Vec2
Vec2::operator / (float scalar) {
    return Vec2(x / scalar, y / scalar);
}

//------------------------------------------------------------
Vec2 & 
Vec2::operator += (Vec2 const & vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

//------------------------------------------------------------
Vec2 & 
Vec2::operator -= (Vec2 const & vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

//------------------------------------------------------------
Vec2 & 
Vec2::operator *= (Vec2 const & vec) {
    x *= vec.x;
    y *= vec.y;
    return *this;
}

//------------------------------------------------------------
Vec2 & 
Vec2::operator /= (Vec2 const & vec) {
    x /= vec.x;
    y /= vec.y;
    return *this;
}

//------------------------------------------------------------
Vec2 & 
Vec2::operator += (float scalar) {
    x += scalar;
    y += scalar;
    return *this;
}

//------------------------------------------------------------
Vec2 &
Vec2::operator -= (float scalar) {
    x -= scalar;
    y -= scalar;
    return *this;
}

//------------------------------------------------------------
Vec2 & 
Vec2::operator *= (float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

//------------------------------------------------------------
Vec2 &
Vec2::operator /= (float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

} /* namespace Maths */