// std
#include <cmath>

namespace Maths {

/* free function operators - (scalar [operator] Vec2) */
//------------------------------------------------------------
inline Vec2
operator + (float lhs, Vec2 const & rhs) {
    return Vec2(lhs + rhs.x, lhs + rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator - (float lhs, Vec2 const & rhs) {
    return Vec2(lhs - rhs.x, lhs - rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator * (float lhs, Vec2 const & rhs) {
    return Vec2(lhs * rhs.x, lhs * rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator / (float lhs, Vec2 const & rhs) {
    return Vec2(lhs / rhs.x, lhs / rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator + (Vec2 const & lhs, float rhs) {
    return Vec2(lhs.x + rhs, lhs.y + rhs);
}

//------------------------------------------------------------
inline Vec2
operator - (Vec2 const & lhs, float rhs) {
    return Vec2(lhs.x - rhs, lhs.y - rhs);
}

//------------------------------------------------------------
inline Vec2
operator * (Vec2 const & lhs, float rhs){
    return Vec2(lhs.x * rhs, lhs.y * rhs);
}

//------------------------------------------------------------
inline Vec2
operator / (Vec2 const & lhs, float rhs) {
    return Vec2(lhs.x / rhs, lhs.y / rhs);
}

//------------------------------------------------------------
inline Vec2
operator + (Vec2 const & lhs, Vec2 const & rhs) {
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator - (Vec2 const & lhs, Vec2 const & rhs) {
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator * (Vec2 const & lhs, Vec2 const & rhs) {
        return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}

//------------------------------------------------------------
inline Vec2
operator / (Vec2 const & lhs, Vec2 const & rhs) {
        return Vec2(lhs.x / rhs.x, lhs.y / rhs.y);
}

/* free function versions of member functions */
//------------------------------------------------------------
inline float
length(Vec2 const & vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

//------------------------------------------------------------
inline float
length2(Vec2 const & vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

//------------------------------------------------------------
inline Vec2
getLongest(Vec2 const & lhs, Vec2 const & rhs) {
    if(length2(lhs) > length2(rhs)) {
        return lhs;
    } else {
        return rhs;
    }
}

//------------------------------------------------------------
inline float
distance(Vec2 const & lhs, Vec2 const & rhs) {
    Vec2 temp =  lhs - rhs;
    return temp.length();
}

//------------------------------------------------------------
inline Vec2
normalise(Vec2 const & vec) {
    float len = length(vec);
    return Vec2(vec.x / len, vec.y / len);
}

//------------------------------------------------------------
inline float
dot(Vec2 const & lhs, Vec2 const & rhs) {
    return (lhs.x * rhs.x + lhs.y * rhs.y);
}

//------------------------------------------------------------
inline std::ostream &
operator << (std::ostream & lhs, Vec2 const & rhs) {
    lhs << "Vec2([x:" << rhs.x << "], [y: " << rhs.y << ")";
    return lhs; 
}

} /* namespace Maths */