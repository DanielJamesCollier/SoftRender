// my
#include "Vec3.hpp"

// std
#include <cmath>

namespace Maths {

//------------------------------------------------------------
Vec3::Vec3(float xyz) :
    x(xyz)
,   y(xyz)
,   z(xyz)
{
    // empty
}

//------------------------------------------------------------
Vec3::Vec3(float _x, float _y, float _z) :
    x(_x)
,   y(_y)
,   z(_z)
{
    // empty
}

//------------------------------------------------------------
float 
Vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

//------------------------------------------------------------
float
Vec3::length2() const {
    return x * x + y * y + z * z;
}

//------------------------------------------------------------
void 
Vec3::normalise() {
    float len = length();
    x /= len;
    y /= len;
    z /= len;
}

//------------------------------------------------------------
float 
Vec3::dot(Vec3 const & vec) const {
    return x * vec.x + y * vec.y + z * z;
}

//------------------------------------------------------------
Vec3
Vec3::cross(Vec3 const & vec) {
    auto x = (y * vec.z) - (z * vec.y);
    auto y = (z * vec.x) - (x * vec.z);
    auto z = (x * vec.y) - (y * vec.x);
    return Vec3(x,y,z);
}

//------------------------------------------------------------
Vec3 
Vec3::operator + () const {
    return *this;
}

//------------------------------------------------------------
Vec3 
Vec3::operator - () const {
    return Vec3(-x, -y, -z);
}

//------------------------------------------------------------
Vec3
Vec3::operator + (Vec3 const & vec) {
    return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

//------------------------------------------------------------
Vec3
Vec3::operator - (Vec3 const & vec) {
    return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

//------------------------------------------------------------
Vec3
Vec3::operator * (Vec3 const & vec) {
    return Vec3(x * vec.x, y * vec.y, z * vec.z);
}

//------------------------------------------------------------
Vec3
Vec3::operator / (Vec3 const & vec) {
    return Vec3(x / vec.x, y / vec.y, z / vec.z);
}

//------------------------------------------------------------
Vec3
Vec3::operator + (float scalar) {
    return Vec3(x + scalar, y + scalar, z + scalar);
}

//------------------------------------------------------------
Vec3
Vec3::operator - (float scalar) {
    return Vec3(x - scalar, y - scalar, z - scalar);
}

//------------------------------------------------------------
Vec3
Vec3::operator * (float scalar) {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

//------------------------------------------------------------
Vec3
Vec3::operator / (float scalar) {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

//------------------------------------------------------------
Vec3 & 
Vec3::operator += (Vec3 const & vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

//------------------------------------------------------------
Vec3 & 
Vec3::operator -= (Vec3 const & vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

//------------------------------------------------------------
Vec3 & 
Vec3::operator *= (Vec3 const & vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

//------------------------------------------------------------
Vec3 & 
Vec3::operator /= (Vec3 const & vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

//------------------------------------------------------------
Vec3 & 
Vec3::operator += (float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

//------------------------------------------------------------
Vec3 &
Vec3::operator -= (float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

//------------------------------------------------------------
Vec3 & 
Vec3::operator *= (float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

//------------------------------------------------------------
Vec3 &
Vec3::operator /= (float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

} /* namespace Maths */