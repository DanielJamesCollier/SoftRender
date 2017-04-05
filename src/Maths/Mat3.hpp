#ifndef Mat3_hpp
#define Mat3_hpp

// std
#include <array>
#include <iostream>

// my 
namespace Maths {

// template forward declarations
template<typename T> class Mat3;
template<typename T> Mat3<T> operator * (Mat3<T> const & lhs, Mat3<T> const & rhs);
template<typename T> std::ostream & operator << (std::ostream & lhs, Mat3<T> const & rhs);

template<typename T>
class Mat3 {
public: // public functions
    Mat3();
    Mat3(std::array<T, 9> matrix);
    ~Mat3() = default;

    void clear();
    void clear(T value);

public: // friend operators - contained in this
    friend Mat3<T> operator *<> (Mat3<T> const & lhs, Mat3<T> const & rhs);
    friend std::ostream & operator <<<> (std::ostream & lhs, Mat3<T> const & rhs);  

private: // private operators
    float & operator [] (int index);
    float const & operator [] (int index) const;

private: // private data
    std::array<T, 9> m_matrix;
};

} /* namespace Maths */
#include "Mat3.inl"
#endif /* Mat3_hpp */