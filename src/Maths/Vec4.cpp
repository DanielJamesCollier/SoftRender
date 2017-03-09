// my
#include "Vec4.hpp"
#include "Vec3.hpp"

namespace Maths {

//------------------------------------------------------------
Vec4::Vec4(float xyz) :
    x(xyz)
,   y(xyz)
,   z(xyz)
,   w(xyz)
{
    // empty
}

//------------------------------------------------------------
Vec4::Vec4(float _x, float _y, float _z, float _w) :
    x(_x)
,   y(_y)
,   z(_z)
,   w(_w)
{
    // empty
}

//------------------------------------------------------------
Vec4::Vec4(Vec3 const & vec, float _w) :
    x(vec.x)
,   y(vec.y)
,   z(vec.z)
,   w(_w)
{

}

//------------------------------------------------------------
Vec3
Vec4::toVec3() {
    return Vec3(x,y,z);
}

//------------------------------------------------------------
Vec4
Vec4::operator + () {
    return *this;
}

//------------------------------------------------------------
Vec4
Vec4::operator - () {
    return Vec4(-x, -y, -z, -w);
}

/* Vec4 OPP Vec4 */
//------------------------------------------------------------
Vec4
Vec4::operator + (Vec4 const & rhs) {
    return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

//------------------------------------------------------------
Vec4 
Vec4::operator - (Vec4 const & rhs) {
    return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

//------------------------------------------------------------
Vec4 
Vec4::operator * (Vec4 const & rhs) {
    return Vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

//------------------------------------------------------------
Vec4
Vec4::operator / (Vec4 const & rhs) {
    return Vec4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
}

/* Vec4 OPP Scalar */
//------------------------------------------------------------
Vec4 
Vec4::operator + (float scalar) {
    return Vec4(x + scalar, y + scalar, z + scalar, w + scalar);
}

//------------------------------------------------------------
Vec4 
Vec4::operator - (float scalar) {
    return Vec4(x - scalar, y - scalar, z - scalar, w - scalar);
}

//------------------------------------------------------------
Vec4
Vec4::operator * (float scalar) {
    return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

//------------------------------------------------------------
Vec4 
Vec4::operator / (float scalar) {
    return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

/* Vec4 Opp= Vec4 */ 
//------------------------------------------------------------
Vec4 &
Vec4::operator += (Vec4 const & rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

//------------------------------------------------------------
Vec4 &
Vec4::operator -= (Vec4 const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

//------------------------------------------------------------
Vec4 &
Vec4::operator *= (Vec4 const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

//------------------------------------------------------------
Vec4 &
Vec4::operator /= (Vec4 const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

/* Vec4 Opp= Vec4 */ 
//------------------------------------------------------------
Vec4 &
Vec4::operator += (float scalar) {
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}

//------------------------------------------------------------
Vec4 &
Vec4::operator -= (float scalar) {
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}

//------------------------------------------------------------
Vec4 &
Vec4::operator *= (float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

//------------------------------------------------------------
Vec4 &
Vec4::operator /= (float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

} /* namespace Maths */