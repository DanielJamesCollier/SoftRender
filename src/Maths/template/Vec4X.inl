// included at the bottom of Vec4X.hpp

namespace Maths {

// RAII

//------------------------------------------------------------
template<typename T>
Vec4X<T>::Vec4X(T all) 
:   x(all)
,   y(all)
,   z(all)
,   w(all)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4X<T>::Vec4X(T _x, T _y, T _z, T _w) 
:   x(_x)
,   y(_y)
,   z(_z)
,   w(_w)
{
    // empty
}

// member - functions

//------------------------------------------------------------
template<typename T> T
Vec4X<T>::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

//------------------------------------------------------------
template<typename T> T
Vec4X<T>::length2() const {
    return x * x + y * y + z * z + w * w;
}

//------------------------------------------------------------
template<typename T> void
Vec4X<T>::normalise() {
    T length = std::sqrt(x * x + y * y + z * z + w * w);
    x /= length;
    y /= length;
    z /= length;
    w /= length;
}

//------------------------------------------------------------
template<typename T> T
Vec4X<T>::dot(Vec4X<T> const & vec) const {
     return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

// member - operator overloads

//------------------------------------------------------------
template<typename T> Vec4X<T>
Vec4X<T>::operator + () const {
    return Vec4X<T>(x, y, z, w);
}

//------------------------------------------------------------
template<typename T> Vec4X<T>
Vec4X<T>::operator - () const {
    return Vec4X<T>(-x, -y, -z, -w);
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator += (Vec4X<T> const & rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator -= (Vec4X<T> const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator *= (Vec4X<T> const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator /= (Vec4X<T> const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator += (T rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator -= (T rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator *= (T rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec4X<T> &
Vec4X<T>::operator /= (T rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

// free function operator overloads

//------------------------------------------------------------
template<typename T> Vec4X<T> 
operator + (Vec4X<T> const & lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4X<T> 
operator - (Vec4X<T> const & lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4X<T> 
operator * (Vec4X<T> const & lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4X<T> 
operator / (Vec4X<T> const & lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
}

//------------------------------------------------------------
template<typename T> Vec4X<T>
operator + (T lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec4X<T>
operator - (T lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec4X<T>
operator * (T lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec4X<T>
operator / (T lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.z);
}

} /* namespace Maths */