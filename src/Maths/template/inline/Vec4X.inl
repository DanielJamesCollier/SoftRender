// included at the bottom of Vec4X.hpp

namespace djc_math {

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

//------------------------------------------------------------
template<typename T>
Vec4X<T>::Vec4X(Vec2X<T> const & vecXY, Vec2X<T> const & vecZW)
:   x(vecXY.x)
,   y(vecXY.y)
,   z(vecZW.x)
,   w(vecZW.y)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4X<T>::Vec4X(Vec2X<T> const & vec, T _z, T _w)
:   x(vec.x)
,   y(vec.y)
,   z(_z)
,   w(_w)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec4X<T>::Vec4X(Vec3X<T> const & vec, T _w) 
:   x(vec.x)
,   y(vec.y)
,   z(vec.z)
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

//------------------------------------------------------------
template<typename T> Vec3X<T>
Vec4X<T>::toVec2X() const {
    return Vec2X<T>(x, y);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
Vec4X<T>::toVec3X() const {
    return Vec3X<T>(x, y, z);
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

//------------------------------------------------------------
template<typename T> std::ostream &
operator << (std::ostream & lhs, Vec4X<T> const & rhs) {
    lhs << "Vec4X(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
}

} /* namespace djc_math */