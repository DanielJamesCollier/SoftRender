namespace Maths {
    
//------------------------------------------------------------
inline Vec4
operator + (float lhs, Vec4 const & rhs) {
    return Vec4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
}

//------------------------------------------------------------
inline Vec4 
operator - (float lhs, Vec4 const & rhs) {
    return Vec4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
}

//------------------------------------------------------------
inline Vec4 
operator * (float lhs, Vec4 const & rhs) {
    return Vec4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
}

//------------------------------------------------------------
inline Vec4 
operator / (float lhs, Vec4 const & rhs) {
    return Vec4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
}

//------------------------------------------------------------
inline std::ostream & 
operator << (std::ostream & lhs, Vec4 const & rhs) {
    lhs << "Vec4(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")" << std::endl;
    return lhs;
}

} /* namespace Maths */