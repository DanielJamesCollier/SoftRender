namespace Maths {

//------------------------------------------------------------
template<typename T>
Mat4<T>::Mat4() {
    m_matrix.fill(T());
}

//------------------------------------------------------------
template<typename T>
Mat4<T>::Mat4(std::array<T, 16> matrix) 
: m_matrix(matrix)
{
    // empty
}

//------------------------------------------------------------
template<typename T> void
Mat4<T>::clear() {
    m_matrix.fill(T());
}

//------------------------------------------------------------
template<typename T> void
Mat4<T>::clear(T value) {
    m_matrix.fill(value);
}

//------------------------------------------------------------
template<typename T> /* friend */ Mat4<T> 
operator * (Mat4<T> const & lhs, Mat4<T> const & rhs) {
    // transforms use column major
    //-------------------- 
    // [0]  [4]  [8]  [12] 
    // [1]  [5]  [9]  [13] 
    // [2]  [6]  [10] [14]
    // [3]  [7]  [11] [15]
    //---------------------
    
    return Mat4<T>(std::array<T, 16>{{
       // column one
       (lhs[0] * rhs[ 0]) + (lhs[4] * rhs[ 1]) + (lhs[ 8] * rhs[ 2]) + (lhs[12] * rhs[ 3]), // 0
       (lhs[1] * rhs[ 0]) + (lhs[5] * rhs[ 1]) + (lhs[ 9] * rhs[ 2]) + (lhs[13] * rhs[ 3]), // 1
       (lhs[2] * rhs[ 0]) + (lhs[6] * rhs[ 1]) + (lhs[10] * rhs[ 2]) + (lhs[14] * rhs[ 3]), // 2
       (lhs[3] * rhs[ 0]) + (lhs[7] * rhs[ 1]) + (lhs[11] * rhs[ 2]) + (lhs[15] * rhs[ 3]), // 3
       // column two
       (lhs[0] * rhs[ 4]) + (lhs[4] * rhs[ 5]) + (lhs[ 8] * rhs[ 6]) + (lhs[12] * rhs[ 7]), // 4
       (lhs[1] * rhs[ 4]) + (lhs[5] * rhs[ 5]) + (lhs[ 9] * rhs[ 6]) + (lhs[13] * rhs[ 7]), // 5
       (lhs[2] * rhs[ 4]) + (lhs[6] * rhs[ 5]) + (lhs[10] * rhs[ 6]) + (lhs[14] * rhs[ 7]), // 6
       (lhs[3] * rhs[ 4]) + (lhs[7] * rhs[ 5]) + (lhs[11] * rhs[ 6]) + (lhs[15] * rhs[ 7]), // 7
       // column three
       (lhs[0] * rhs[ 8]) + (lhs[4] * rhs[ 9]) + (lhs[ 8] * rhs[10]) + (lhs[12] * rhs[11]), // 8
       (lhs[1] * rhs[ 8]) + (lhs[5] * rhs[ 9]) + (lhs[ 9] * rhs[10]) + (lhs[13] * rhs[11]), // 9
       (lhs[2] * rhs[ 8]) + (lhs[6] * rhs[ 9]) + (lhs[10] * rhs[10]) + (lhs[14] * rhs[11]), // 10
       (lhs[3] * rhs[ 8]) + (lhs[7] * rhs[ 9]) + (lhs[11] * rhs[10]) + (lhs[15] * rhs[11]), // 11
       // column four
       (lhs[0] * rhs[12]) + (lhs[4] * rhs[13]) + (lhs[ 8] * rhs[14]) + (lhs[12] * rhs[15]), // 12
       (lhs[1] * rhs[12]) + (lhs[5] * rhs[13]) + (lhs[ 9] * rhs[14]) + (lhs[13] * rhs[15]), // 13
       (lhs[2] * rhs[12]) + (lhs[6] * rhs[13]) + (lhs[10] * rhs[14]) + (lhs[14] * rhs[15]), // 14
       (lhs[3] * rhs[12]) + (lhs[7] * rhs[13]) + (lhs[11] * rhs[14]) + (lhs[15] * rhs[15])  // 15
    }});
}

//------------------------------------------------------------
template<typename T> /* friend */ Vec4X<T> 
operator * (Mat4<T> const & lhs, Vec4X<T> const & rhs) {
    return Vec4X<T>(
        (lhs[0] * rhs.x) + (lhs[4] + rhs.y) + (lhs[ 8] + rhs.z) + (lhs[12] + rhs.w),
        (lhs[1] * rhs.x) + (lhs[5] + rhs.y) + (lhs[ 9] + rhs.z) + (lhs[13] + rhs.w),
        (lhs[2] * rhs.x) + (lhs[6] + rhs.y) + (lhs[10] + rhs.z) + (lhs[14] + rhs.w),
        (lhs[3] * rhs.x) + (lhs[7] + rhs.y) + (lhs[11] + rhs.z) + (lhs[15] + rhs.w)
    );
}

//------------------------------------------------------------
template<typename T> /* friend */ std::ostream & 
operator << (std::ostream & lhs, Mat4<T> const & rhs) {
    lhs << "Mat4\n-----------------\n";
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
                lhs << "[" << rhs.m_matrix[4 * x + y] << "] "; 
        }
          lhs << "\n";
    }
    lhs << "-----------------";
    return lhs;
}

//------------------------------------------------------------
template<typename T> float & 
Mat4<T>::operator [] (std::size_t index) {
    return m_matrix[index];
}

//------------------------------------------------------------
template<typename T> float const & 
Mat4<T>::operator [] (std::size_t index) const {
    return m_matrix[index];
}


} /* namespace Maths */