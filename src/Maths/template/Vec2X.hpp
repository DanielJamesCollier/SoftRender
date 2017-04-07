#ifndef Vec2X_hpp
#define Vec2X_hpp

#include <cmath>

namespace Maths {

template<typename T>
class Vec2X {
public: // RAII
    explicit Vec2X(T all = T());
    Vec2X(T _x, T _y);
    ~Vec2X() = default;

public: // member - functions
     T length() const;
     T length2() const;
     void normalise();
     T dot(Vec2X<T> const & vec);

public: // member - operator overloads
    Vec2X<T>   operator + () const;
    Vec2X<T>   operator - () const;
    
    Vec2X<T> & operator += (Vec2X<T> const & rhs);
    Vec2X<T> & operator -= (Vec2X<T> const & rhs);
    Vec2X<T> & operator *= (Vec2X<T> const & rhs);
    Vec2X<T> & operator /= (Vec2X<T> const & rhs);

    Vec2X<T> & operator += (T rhs);
    Vec2X<T> & operator -= (T rhs);
    Vec2X<T> & operator *= (T rhs);
    Vec2X<T> & operator /= (T rhs);


public: // free function operator overloads - defined in Vec2X.inl
    // Vec2X<T> operator + (Vec2X<T> const & lhs, Vec2X<T> const & rhs);
    // Vec2X<T> operator - (Vec2X<T> const & lhs, Vec2X<T> const & rhs);
    // Vec2X<T> operator * (Vec2X<T> const & lhs, Vec2X<T> const & rhs);
    // Vec2X<T> operator / (Vec2X<T> const & lhs, Vec2X<T> const & rhs);

    // Vec2X<T> operator + (T lhs, Vec2X<T> const & rhs);
    // Vec2X<T> operator - (T lhs, Vec2X<T> const & rhs);
    // Vec2X<T> operator * (T lhs, Vec2X<T> const & rhs);
    // Vec2X<T> operator / (T lhs, Vec2X<T> const & rhs);

    // Vec2X<T> operator + (Vec2X<T> const & lhs, float rhs);
    // Vec2X<T> operator - (Vec2X<T> const & lhs, float rhs);
    // Vec2X<T> operator * (Vec2X<T> const & lhs, float rhs);
    // Vec2X<T> operator / (Vec2X<T> const & lhs, float rhs);

public: // free function operator overload for use with other classes
    // Vec2X<T> operator * (Mat2<T> const & rhs & lhs, Vec2<T> const & rhs); - defined in Mat2.inl

public:
    T x;
    T y;
};
} /* namespace Maths */
#include "Vec2X.inl"
#endif /* Vec2X<T>_hpp */