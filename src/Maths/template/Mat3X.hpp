#ifndef Mat3X_hpp
#define Mat3X_hpp

// std
#include <array>
#include <iostream>
#include <cstddef> // std::size_t

// my 
#include "Vec3X.hpp"

namespace djc_math {

// template forward declarations
template<typename T> class Mat3X;
template<typename T> Mat3X<T> operator * (Mat3X<T> const & lhs, Mat3X<T> const & rhs);
template<typename T> Vec3X<T> operator * (Mat3X<T> const & lhs, Vec3X<T> const & rhs);
template<typename T> std::ostream & operator << (std::ostream & lhs, Mat3X<T> const & rhs);

template<typename T = float>
class Mat3X final {
public: // RAII
    Mat3X();
    explicit Mat3X(std::array<T, 9> matrix);
    ~Mat3X() = default;

public: // friend free functions
    // friend void clear();
    // friend void clear(T value);

public: // friend operators - defined in Mat3X.inl
    friend Mat3X<T> operator *<> (Mat3X<T> const & lhs, Mat3X<T> const & rhs);
    friend Vec3X<T> operator *<> (Mat3X<T> const & lhs, Vec3X<T> const & rhs);
    friend std::ostream & operator <<<> (std::ostream & lhs, Mat3X<T> const & rhs);  

private: // private operators
    float & operator [] (std::size_t index);
    float const & operator [] (std::size_t index) const;

private: // private data
    std::array<T, 9> m_matrix;
};

} /* namespace djc_math */
#include "inline/Mat3X.inl"
#endif /* Mat3X_hpp */