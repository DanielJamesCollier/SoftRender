#ifndef Mat4X_hpp
#define Mat4X_hpp

// std
#include <array>
#include <iostream>
#include <cstddef> // for std::size_t

// my
#include "Vec4X.hpp"
#include "Mat3X.hpp"

namespace djc_math {

// template forward declarations
template<typename T> class Mat4X;
template<typename T> Mat4X<T> operator * (Mat4X<T> const & lhs, Mat4X<T> const & rhs);
template<typename T> Vec4X<T> operator * (Mat4X<T> const & lhs, Vec4X<T> const & rhs);
template<typename T> std::ostream & operator << (std::ostream & lhs, Mat4X<T> const & rhs);

template<typename T = float>
class Mat4X final {
public: // RAII
    Mat4X();
    explicit Mat4X(std::array<T, 16> matrix);
    ~Mat4X() = default;

public: // member - functions
    Mat3X<T> toMat3X() const;

public: // public friend free functions
    // friend void clear();
    // friend void clear(T value);

public: // friend free operators - defined in Mat4X.inl
    friend Mat4X<T> operator *<> (Mat4X<T> const & lhs, Mat4X<T> const & rhs);
    friend Vec4X<T> operator *<> (Mat4X<T> const & lhs, Vec4X<T> const & rhs);
    friend std::ostream & operator <<<> (std::ostream & lhs, Mat4X<T> const & rhs);  

private: // private operators
    float & operator [] (std::size_t index);
    float const & operator [] (std::size_t index) const;

private: // private data
    std::array<T, 16> m_matrix;
};
} /* namespace djc_math */
#include "inline/Mat4X.inl"
#endif /* Mat4X_hpp */