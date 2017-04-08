#ifndef Vec4X_hpp
#define Vec4X_hpp

// std
#include <cmath>
#include <iostream>

// my
#include "Vec2X.hpp"
#include "Vec3X.hpp"

namespace djc_math {

template<typename T = float>
class Vec4X final {
public: // RAII
    explicit Vec4X(T all = T());
    Vec4X(T _x, T _y, T _z, T _w);
    Vec4X(Vec2X<T> const & vec, T _z, T _w);
    Vec4X(Vec2X<T> const & vecXY, Vec2X<T> const & vecZW);
    Vec4X(Vec3X<T> const & vec, T _w);
    ~Vec4X() = default;

public: // member - functions
    T length() const;
    T length2() const;
    void normalise();
    T dot(Vec4X<T> const & vec) const;
    // for cross cast to Vec3
    Vec3X<T> toVec2X() const;
    Vec3X<T> toVec3X() const;

public: // member - operator overloads

    Vec4X<T> operator + () const;
    Vec4X<T> operator - () const;

    Vec4X<T> & operator += (Vec4X<T> const & rhs);
    Vec4X<T> & operator -= (Vec4X<T> const & rhs);
    Vec4X<T> & operator *= (Vec4X<T> const & rhs);
    Vec4X<T> & operator /= (Vec4X<T> const & rhs);

    Vec4X<T> & operator += (T rhs);
    Vec4X<T> & operator -= (T rhs);
    Vec4X<T> & operator *= (T rhs);
    Vec4X<T> & operator /= (T rhs);

public: // free function operator overloads - defined in Vec4X.inl
    // Vec4X<T> operator + (Vec4X<T> const & lhs, Vec4X<T> const & rhs);
    // Vec4X<T> operator - (Vec4X<T> const & lhs, Vec4X<T> const & rhs);
    // Vec4X<T> operator * (Vec4X<T> const & lhs, Vec4X<T> const & rhs);
    // Vec4X<T> operator / (Vec4X<T> const & lhs, Vec4X<T> const & rhs);

    // Vec4X<T> operator + (T lhs, Vec4X<T> const & rhs);
    // Vec4X<T> operator - (T lhs, Vec4X<T> const & rhs);
    // Vec4X<T> operator * (T lhs, Vec4X<T> const & rhs);
    // Vec4X<T> operator / (T lhs, Vec4X<T> const & rhs);

    // Vec4X<T> operator + (Vec4X<T> const & lhs, float rhs);
    // Vec4X<T> operator - (Vec4X<T> const & lhs, float rhs);
    // Vec4X<T> operator * (Vec4X<T> const & lhs, float rhs);
    // Vec4X<T> operator / (Vec4X<T> const & lhs, float rhs);
    // std::ostream & operator << (std::ostream & lhs, Vec4X<T> const & rhs);  

public: // free function operator overload for use with other classes - defined in Vec34.inl
    // Vec4X<T> operator * (Mat4<T> const & rhs & lhs, Vec4X<T> const & rhs); - defined in Mat4.inl

public: // public data
    T x;
    T y;
    T z;
    T w;
};

} /* namespace djc_math */
#include "inline/Vec4X.inl"
#endif /* Vec4X_hpp */