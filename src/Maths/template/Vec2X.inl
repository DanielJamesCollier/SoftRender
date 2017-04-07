namespace Maths {

// RAII

//------------------------------------------------------------
template<typename T>
Vec2X<T>::Vec2X(T all) 
:   x(all)
,   y(all)
{
    // empty
}

//------------------------------------------------------------
template<typename T>
Vec2X<T>::Vec2X(T _x, T _y) 
:   x(_x)
,   y(_y)
{
    // empty
}

// member - functions

//------------------------------------------------------------
template<typename T> T
Vec2X<T>::length() const {
    return std::sqrt(x * x + y * y);
}

//------------------------------------------------------------
template<typename T> T
Vec2X<T>::length2() const {
    return x * x + y * y;
}

//------------------------------------------------------------
template<typename T> void
Vec2X<T>::normalise() {
    T length = std::sqrt(x * x + y * y);
    x /= length;
    y /= length;
}

//------------------------------------------------------------
template<typename T> T
Vec2X<T>::dot(Vec2X<T> const & vec) {
    return x * vec.x + y * vec.y;
}

// member - operator overloads

//------------------------------------------------------------
template<typename T> Vec2X<T> 
Vec2X<T>::operator + () const {
    return Vec2X<T>(x, y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T> 
Vec2X<T>::operator - () const {
    return Vec2X<T>(-x, -y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator += (Vec2X<T> const & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator -= (Vec2X<T> const & rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator *= (Vec2X<T> const & rhs) {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator /= (Vec2X<T> const & rhs) {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator += (T rhs) {
    x += rhs;
    y += rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator -= (T rhs) {
    x -= rhs;
    y -= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator *= (T rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

//------------------------------------------------------------
template<typename T> Vec2X<T> &
Vec2X<T>::operator /= (T rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
}

// free function operator overloads

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator + (Vec2X<T> const & lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator - (Vec2X<T> const & lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator * (Vec2X<T> const & lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator / (Vec2X<T> const & lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator + (T lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs + rhs.x, lhs + rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator - (T lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs - rhs.x, lhs - rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator * (T lhs, Vec2X<T> const & rhs) {
    return Vec2X<T>(lhs * rhs.x, lhs * rhs.y);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator + (Vec2X<T> const & lhs, T rhs) {
    return Vec2X<T>(lhs.x + rhs, lhs.y + rhs);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator - (Vec2X<T> const & lhs, T rhs) {
    return Vec2X<T>(lhs.x - rhs, lhs.y - rhs);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator * (Vec2X<T> const & lhs, T rhs) {
    return Vec2X<T>(lhs.x * rhs, lhs.y * rhs);
}

//------------------------------------------------------------
template<typename T> Vec2X<T>
operator / (Vec2X<T> const & lhs, T rhs) {
    return Vec2X<T>(lhs.x / rhs, lhs.y / rhs);
}

} /* namespace Maths */