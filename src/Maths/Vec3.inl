/* free function operators - (scalar [operator] Vec3) */
//------------------------------------------------------------
inline Vec3
operator += (float lhs, Vec3 const & rhs) {
    return Vec3(lhs + rhs.m_data[0], lhs + rhs.m_data[1], lhs + rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator -= (float lhs, Vec3 const & rhs) {
    return Vec3(lhs - rhs.m_data[0], lhs - rhs.m_data[1], lhs - rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator *= (float lhs, Vec3 const & rhs) {
    return Vec3(lhs * rhs.m_data[0], lhs * rhs.m_data[1], lhs * rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator /= (float lhs, Vec3 const & rhs) {
    return Vec3(lhs / rhs.m_data[0], lhs / rhs.m_data[1], lhs / rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator + (float lhs, Vec3 const & rhs) {
    return Vec3(lhs + rhs.m_data[0], lhs + rhs.m_data[1], lhs + rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator - (float lhs, Vec3 const & rhs) {
    return Vec3(lhs - rhs.m_data[0], lhs - rhs.m_data[1], lhs - rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator * (float lhs, Vec3 const & rhs) {
    return Vec3(lhs * rhs.m_data[0], lhs * rhs.m_data[1], lhs * rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator / (float lhs, Vec3 const & rhs) {
    return Vec3(lhs / rhs.m_data[0], lhs / rhs.m_data[1], lhs / rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator + (Vec3 const & lhs, float rhs) {
    return Vec3(lhs.m_data[0] + rhs, lhs.m_data[1] + rhs, lhs.m_data[2] + rhs);
}

//------------------------------------------------------------
inline Vec3
operator - (Vec3 const & lhs, float rhs) {
    return Vec3(lhs.m_data[0] - rhs, lhs.m_data[1] - rhs, lhs.m_data[2] - rhs);
}

//------------------------------------------------------------
inline Vec3
operator * (Vec3 const & lhs, float rhs){
    return Vec3(lhs.m_data[0] * rhs, lhs.m_data[1] * rhs, lhs.m_data[2] * rhs);
}

//------------------------------------------------------------
inline Vec3
operator / (Vec3 const & lhs, float rhs) {
    return Vec3(lhs.m_data[0] / rhs, lhs.m_data[1] / rhs, lhs.m_data[2] / rhs);
}

//------------------------------------------------------------
inline Vec3
operator + (Vec3 const & lhs, Vec3 const & rhs) {
    return Vec3(lhs.m_data[0] + rhs.m_data[0], lhs.m_data[1] + rhs.m_data[1], lhs.m_data[2] + rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator - (Vec3 const & lhs, Vec3 const & rhs) {
    return Vec3(lhs.m_data[0] - rhs.m_data[0], lhs.m_data[1] - rhs.m_data[1], lhs.m_data[2] - rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator * (Vec3 const & lhs, Vec3 const & rhs) {
        return Vec3(lhs.m_data[0] * rhs.m_data[0], lhs.m_data[1] * rhs.m_data[1], lhs.m_data[2] * rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
operator / (Vec3 const & lhs, Vec3 const & rhs) {
        return Vec3(lhs.m_data[0] / rhs.m_data[0], lhs.m_data[1] / rhs.m_data[1], lhs.m_data[2] / rhs.m_data[2]);
}

/* free function versions of member functions */
//------------------------------------------------------------
inline float
length(Vec3 const & vec) {
    return std::sqrt(vec.m_data[0] * vec.m_data[0] + vec.m_data[1] * vec.m_data[1] + vec.m_data[2] * vec.m_data[2]);
}

//------------------------------------------------------------
inline float
length2(Vec3 const & vec) {
    return vec.m_data[0] * vec.m_data[0] + vec.m_data[1] * vec.m_data[1] + vec.m_data[2] * vec.m_data[2];
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
    return Vec3(vec.m_data[0] / len, vec.m_data[1] / len, vec.m_data[2] / len);
}

//------------------------------------------------------------
inline float
dot(Vec3 const & lhs, Vec3 const & rhs) {
    return (lhs.m_data[0] * rhs.m_data[0] + lhs.m_data[1] * rhs.m_data[1] + lhs.m_data[2] * rhs.m_data[2]);
}

//------------------------------------------------------------
inline Vec3
cross(Vec3 const & lhs, Vec3 const & rhs) {
    auto x = (lhs.m_data[1] * rhs.m_data[2]) - (lhs.m_data[2] * rhs.m_data[1]);
    auto y = (lhs.m_data[2] * rhs.m_data[0]) - (lhs.m_data[0] * rhs.m_data[2]);
    auto z = (lhs.m_data[0] * rhs.m_data[1]) - (lhs.m_data[1] * rhs.m_data[0]);
    return Vec3(x,y,z);
}

//------------------------------------------------------------
inline std::ostream &
operator << (std::ostream & lhs, Vec3 const & rhs) {
    lhs << "Vec3([x:" << rhs.m_data[0] << "], [y: " << rhs.m_data[1] << "], [z: " << rhs.m_data[2] << "])\n";
    return lhs; 
}
