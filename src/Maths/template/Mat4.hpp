#ifndef Mat4_hpp
#define Mat4_hpp

// std
#include <array>
#include <iostream>
#include <cstddef> // for std::size_t

// my
#include "Vec4X.hpp"

namespace Maths {

// template forward declarations
template<typename T> class Mat4;
template<typename T> Mat4<T> operator * (Mat4<T> const & lhs, Mat4<T> const & rhs);
template<typename T> Vec4X<T> operator * (Mat4<T> const & lhs, Vec4X<T> const & rhs);
template<typename T> std::ostream & operator << (std::ostream & lhs, Mat4<T> const & rhs);

template<typename T = float>
class Mat4 final {
public: // public funtions
    Mat4();
    explicit Mat4(std::array<T, 16> matrix);
    ~Mat4() = default;

    void clear();
    void clear(T value); // todo : change to free function

public: // public friend free functions
    friend Mat4<T> operator *<> (Mat4<T> const & lhs, Mat4<T> const & rhs);
    friend Vec4X<T> operator *<> (Mat4<T> const & lhs, Vec4X<T> const & rhs);
    friend std::ostream & operator <<<> (std::ostream & lhs, Mat4<T> const & rhs);  

private: // private operators
    float & operator [] (std::size_t index);
    float const & operator [] (std::size_t index) const;

private: // private data
    std::array<T, 16> m_matrix;
};
} /* namespace Maths */
#include "Mat4.inl"
#endif /* Mat4_hpp */