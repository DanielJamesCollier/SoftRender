namespace Maths {

//------------------------------------------------------------
template<typename T>
Mat3<T>::Mat3() {
    m_matrix.fill(T());
}

//------------------------------------------------------------
template<typename T>
Mat3<T>::Mat3(std::array<T, 9> matrix)
: m_matrix(matrix) 
{
    // empty
}

//------------------------------------------------------------
template<typename T> void
Mat3<T>::clear() {
    m_matrix.fill(T());
}

//------------------------------------------------------------
template<typename T> void
Mat3<T>::clear(T value) {
    m_matrix.fill(value);
}

//------------------------------------------------------------
template<typename T> /* friend */ Mat3<T> 
operator * (Mat3<T> const & lhs, Mat3<T> const & rhs) {

    // transforms use column major
    //-------------------- 
    //   [0]  [3]  [6] 
    //   [1]  [4]  [7]   
    //   [2]  [5]  [8] 
    //---------------------
    
    return Mat3<T>(std::array<T, 9>{{
        // column 0
        (lhs[0] * rhs[0]) + (lhs[3] * rhs[1]) + (lhs[6] * rhs[2]), // 0
        (lhs[1] * rhs[0]) + (lhs[4] * rhs[1]) + (lhs[7] * rhs[2]), // 1
        (lhs[2] * rhs[0]) + (lhs[5] * rhs[1]) + (lhs[8] * rhs[2]), // 2
        // column 1
        (lhs[0] * rhs[3]) + (lhs[3] * rhs[4]) + (lhs[6] * rhs[5]), // 3
        (lhs[1] * rhs[3]) + (lhs[4] * rhs[4]) + (lhs[7] * rhs[5]), // 4
        (lhs[2] * rhs[3]) + (lhs[5] * rhs[4]) + (lhs[8] * rhs[5]), // 5
        // column 2
        (lhs[0] * rhs[6]) + (lhs[3] * rhs[7]) + (lhs[6] * rhs[8]), // 6
        (lhs[1] * rhs[6]) + (lhs[4] * rhs[7]) + (lhs[7] * rhs[8]), // 7
        (lhs[2] * rhs[6]) + (lhs[5] * rhs[7]) + (lhs[8] * rhs[8]), // 8
    }});
}

//------------------------------------------------------------
template<typename T> Vec3X<T>
operator * (Mat3<T> const & lhs, Vec3X<T> const & rhs) {
    return Vec3X<T>((lhs[0] * rhs.x) + (lhs[3] * rhs.y) + (lhs[6] * rhs.z),
                    (lhs[1] * rhs.x) + (lhs[4] * rhs.y) + (lhs[7] * rhs.z),
                    (lhs[2] * rhs.x) + (lhs[5] * rhs.y) + (lhs[8] * rhs.z));
}

//------------------------------------------------------------
template<typename T> /* friend */ std::ostream & 
operator << (std::ostream & lhs, Mat3<T> const & rhs) {

    lhs << " Mat3f\n-----------------\n";
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
                lhs << "[" << rhs.m_matrix[3 * x + y] << "] "; 
        }
        lhs << "\n";
    }
    lhs << "-----------------";
    return lhs;
}

//------------------------------------------------------------
template<typename T> float & 
Mat3<T>::operator [] (std::size_t index) {
    return m_matrix[index];
}

//------------------------------------------------------------
template<typename T> float const & 
Mat3<T>::operator [] (std::size_t index) const {
    return m_matrix[index];
}

} /* namespace Maths */