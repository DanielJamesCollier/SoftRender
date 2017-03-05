#include <cmath>
#include <iostream>

namespace Maths {
    
//------------------------------------------------------------
inline Mat4f
operator * (Mat4f & lhs, Mat4f & rhs) {
    Mat4f matrix;

    // transforms use column major
    //-------------------- 
    // [0]  [4]  [8]  [12] 
    // [1]  [5]  [9]  [13] 
    // [2]  [6]  [10] [14]
    // [3]  [7]  [11] [15]
    //---------------------

    // C = A * B

    // C = matrix
    // A = lhs
    // B = rhs
    

    /* first row */
    //C[0]
    matrix[0]  = (lhs[0] * rhs[0])  + (lhs[4] * rhs[1])  + (lhs[8] * rhs[2])  + (lhs[12] * rhs[3]);
    matrix[4]  = (lhs[0] * rhs[4])  + (lhs[4] * rhs[5])  + (lhs[8] * rhs[6])  + (lhs[12] * rhs[7]);
    matrix[8]  = (lhs[0] * rhs[8])  + (lhs[4] * rhs[9])  + (lhs[8] * rhs[10]) + (lhs[12] * rhs[11]);
    matrix[12] = (lhs[0] * rhs[12]) + (lhs[4] * rhs[13]) + (lhs[8] * rhs[14]) + (lhs[12] * rhs[15]);

    /* second row */
    matrix[1]  = (lhs[1] * rhs[0])  + (lhs[5] * rhs[1])  + (lhs[9] * rhs[2])  + (lhs[13] * rhs[3]);
    matrix[5]  = (lhs[1] * rhs[4])  + (lhs[5] * rhs[5])  + (lhs[9] * rhs[6])  + (lhs[13] * rhs[7]);
    matrix[6]  = (lhs[1] * rhs[8])  + (lhs[5] * rhs[9])  + (lhs[9] * rhs[10]) + (lhs[13] * rhs[11]);
    matrix[13] = (lhs[1] * rhs[12]) + (lhs[5] * rhs[13]) + (lhs[9] * rhs[14]) + (lhs[13] * rhs[15]);

    /* third row */
    matrix[2]  = (lhs[2] * rhs[0])  + (lhs[6] * rhs[1])  + (lhs[10] * rhs[2])  + (lhs[14] * rhs[3]);
    matrix[6]  = (lhs[2] * rhs[4])  + (lhs[6] * rhs[5])  + (lhs[10] * rhs[6])  + (lhs[14] * rhs[7]);
    matrix[10] = (lhs[2] * rhs[8])  + (lhs[6] * rhs[9])  + (lhs[10] * rhs[10]) + (lhs[14] * rhs[11]);
    matrix[14] = (lhs[2] * rhs[12]) + (lhs[6] * rhs[13]) + (lhs[10] * rhs[14]) + (lhs[14] * rhs[15]);

    /* second row */
    matrix[3]  = (lhs[3] * rhs[0])  + (lhs[7] * rhs[1])  + (lhs[11] * rhs[2])  + (lhs[15] * rhs[3]);
    matrix[7]  = (lhs[3] * rhs[4])  + (lhs[7] * rhs[5])  + (lhs[11] * rhs[6])  + (lhs[15] * rhs[7]);
    matrix[11] = (lhs[3] * rhs[8])  + (lhs[7] * rhs[9])  + (lhs[11] * rhs[10]) + (lhs[15] * rhs[11]);
    matrix[15] = (lhs[3] * rhs[12]) + (lhs[7] * rhs[13]) + (lhs[11] * rhs[14]) + (lhs[15] * rhs[15]);
    return matrix;
}

//------------------------------------------------------------
inline Vec3 
operator * (Mat4f & lhs, Vec3 const & rhs) {
    float x = rhs.getX();
    float y = rhs.getY();
    float z = rhs.getZ();
    float w = 1;
    Vec3 vec;
    vec.setX(lhs[0] * x + lhs[4] * y + lhs[8] * z + lhs[12] * w);
    vec.setY(lhs[1] * x + lhs[5] * y + lhs[9] * z + lhs[13] * w);
    vec.setZ(lhs[2] * x + lhs[6] * y + lhs[10] * z + lhs[14] * w);
    return vec;
}

//------------------------------------------------------------
inline Vec4 
operator * (Mat4f & lhs, Vec4 const & rhs) {
    float x = rhs.x;
    float y = rhs.y;
    float z = rhs.z;
    float w = rhs.w;

    Vec4 vec;
    vec.x = lhs[0] * x + lhs[4] * y + lhs[8]  * z + lhs[12] * w;
    vec.y = lhs[1] * x + lhs[5] * y + lhs[9]  * z + lhs[13] * w;
    vec.z = lhs[2] * x + lhs[6] * y + lhs[10] * z + lhs[14] * w;
    vec.w = lhs[3] * x + lhs[7] * y + lhs[11] * z + lhs[15] * w;
    return vec;
    }

//------------------------------------------------------------
inline std::ostream &
operator << (std::ostream & lhs, Mat4f const & rhs) {
    
    auto offset = [](int x, int y) {
        return 4 * x + y;
    };

    lhs << "Mat4f\n-----------------\n";
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
                lhs << "[" << rhs.m_data[offset(x,y)] << "] "; 
        }
        lhs << std::endl;
    }
    return lhs;
}

} /* namespace Maths */