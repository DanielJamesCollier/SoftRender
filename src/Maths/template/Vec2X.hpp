#ifndef Vec2X_hpp
#define Vec2X_hpp

// std
#include <cmath>

namespace djc_math {

template<typename T = float>
class Vec2X final {
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

    // std::ostream & operator << (std::ostream & lhs, Vec2X<T> const & rhs);  

public: // free function operator overload for use with other classes
    // Vec2X<T> operator * (Mat2<T> const & rhs & lhs, Vec2<T> const & rhs); - defined in Mat2.inl

public:
    T x;
    T y;
};
} /* namespace djc_math */
#include "inline/Vec2X.inl"
#endif /* Vec2X_hpp */