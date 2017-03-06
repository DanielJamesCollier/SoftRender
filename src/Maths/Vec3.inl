#include <cmath>

namespace Maths {

/* free function operators - (scalar [operator] Vec3) */
//------------------------------------------------------------
inline Vec3
operator += (float lhs, Vec3 const & rhs) {
    return Vec3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator -= (float lhs, Vec3 const & rhs) {
    return Vec3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator *= (float lhs, Vec3 const & rhs) {
    return Vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator /= (float lhs, Vec3 const & rhs) {
    return Vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator + (float lhs, Vec3 const & rhs) {
    return Vec3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator - (float lhs, Vec3 const & rhs) {
    return Vec3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator * (float lhs, Vec3 const & rhs) {
    return Vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator / (float lhs, Vec3 const & rhs) {
    return Vec3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator + (Vec3 const & lhs, float rhs) {
    return Vec3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

//------------------------------------------------------------
inline Vec3
operator - (Vec3 const & lhs, float rhs) {
    return Vec3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
}

//------------------------------------------------------------
inline Vec3
operator * (Vec3 const & lhs, float rhs){
    return Vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

//------------------------------------------------------------
inline Vec3
operator / (Vec3 const & lhs, float rhs) {
    return Vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

//------------------------------------------------------------
inline Vec3
operator + (Vec3 const & lhs, Vec3 const & rhs) {
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator - (Vec3 const & lhs, Vec3 const & rhs) {
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator * (Vec3 const & lhs, Vec3 const & rhs) {
        return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

//------------------------------------------------------------
inline Vec3
operator / (Vec3 const & lhs, Vec3 const & rhs) {
        return Vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

/* free function versions of member functions */
//------------------------------------------------------------
inline float
length(Vec3 const & vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

//------------------------------------------------------------
inline float
length2(Vec3 const & vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

//------------------------------------------------------------
inline Vec3
getLongest(Vec3 const & lhs, Vec3 const & rhs) {
    if(Maths::length2(lhs) > Maths::length2(rhs)) {
        return lhs;
    } else {
        return rhs;
    }
}

//------------------------------------------------------------
inline float
distance(Vec3 const & lhs, Vec3 const & rhs) {
    Vec3 temp =  lhs - rhs;
    return temp.length();
}

//------------------------------------------------------------
inline Vec3
normalise(Vec3 const & vec) {
    float len = length(vec);
    return Vec3(vec.x / len, vec.y / len, vec.z / len);
}

//------------------------------------------------------------
inline float
dot(Vec3 const & lhs, Vec3 const & rhs) {
    return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

//------------------------------------------------------------
inline Vec3
cross(Vec3 const & lhs, Vec3 const & rhs) {
    auto x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
    auto y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
    auto z = (lhs.x * rhs.y) - (lhs.y * rhs.x);
    return Vec3(x,y,z);
}

//------------------------------------------------------------
inline std::ostream &
operator << (std::ostream & lhs, Vec3 const & rhs) {
    lhs << "Vec3([x:" << rhs.x << "], [y: " << rhs.y << "], [z: " << rhs.z << "])\n";
    return lhs; 
}

} /* namespace Maths */
