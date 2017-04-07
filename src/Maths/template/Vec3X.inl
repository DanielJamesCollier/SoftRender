namespace Maths {

// RAII

//------------------------------------------------------------
template<typename T> 
Vec3X<T>::Vec3X(T all) 
:   x(all)
,   y(all)
,   z(all) 
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec3X<T>::Vec3X(T _x, T _y, T _z) 
: x(_x)
, y(_y)
, z(_z)
{
    // empty
}

// member - functions

//------------------------------------------------------------
template<typename T> T
Vec3X<T>::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

//------------------------------------------------------------
template<typename T> T
Vec3X<T>::length2() const {
    return x * x + y * y + z * z;
}

//------------------------------------------------------------
template<typename T> void
Vec3X<T>::normalise() {
    T length = std::sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;
}

//------------------------------------------------------------
template<typename T> T
Vec3X<T>::dot(Vec3X<T> const & vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
Vec3X<T>::cross(Vec3X<T> const & vec) const {
    T x = (y * vec.z) - (z * vec.y);
    T y = (z * vec.x) - (x * vec.z);
    T z = (x * vec.y) - (y * vec.x);
    return Vec3X<T>(x, y, z);
}

// member - operator overloads

//------------------------------------------------------------
template<typename T> Vec3X<T>
Vec3X<T>::operator + () const {
    return Vec3X<T>(x, y, z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
Vec3X<T>::operator - () const {
    return Vec3X<T>(-x, -y, -z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator += (Vec3X<T> const & rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator -= (Vec3X<T> const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator *= (Vec3X<T> const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator /= (Vec3X<T> const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator += (T rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator -= (T rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator *= (T rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec3X<T> &
Vec3X<T>::operator /= (T rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

// free function operator overloads

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator + (Vec3X<T> const & lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator - (Vec3X<T> const & lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator * (Vec3X<T> const & lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator / (Vec3X<T> const & lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator + (T lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator - (T lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator * (T lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator / (T lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator + (Vec3X<T> const & lhs, T rhs) {
    return Vec3X<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator - (Vec3X<T> const & lhs, T rhs) {
    return Vec3X<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator * (Vec3X<T> const & lhs, T rhs) {
    return Vec3X<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator / (Vec3X<T> const & lhs, T rhs) {
    return Vec3X<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}


} /* namespace Maths */