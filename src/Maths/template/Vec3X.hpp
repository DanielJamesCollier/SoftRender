#ifndef Vec3X_hpp
#define Vec3X_hpp


namespace Maths {

template<typename T = float>
class Vec3X final {
public: // RAII
    explicit Vec3X(T all = T());
    Vec3X(T _x, T _y, T _z);
    ~Vec3X() = default;

public: // member - functions
    T length() const;
    T length2() const;
    void normalise();
    T dot(Vec3X<T> const & vec) const;
    Vec3X<T> cross(Vec3X<T> const & vec) const;

public:  // member - operator overloads
    Vec3X<T> operator + () const;
    Vec3X<T> operator - () const;

    Vec3X<T> & operator += (Vec3X<T> const & rhs);
    Vec3X<T> & operator -= (Vec3X<T> const & rhs);
    Vec3X<T> & operator *= (Vec3X<T> const & rhs);
    Vec3X<T> & operator /= (Vec3X<T> const & rhs);

    Vec3X<T> & operator += (T rhs);
    Vec3X<T> & operator -= (T rhs);
    Vec3X<T> & operator *= (T rhs);
    Vec3X<T> & operator /= (T rhs);

public: // free function operator overloads - defined in Vec3X.inl
    // Vec3X<T> operator + (Vec3X<T> const & lhs, Vec3X<T> const & rhs);
    // Vec3X<T> operator - (Vec3X<T> const & lhs, Vec3X<T> const & rhs);
    // Vec3X<T> operator * (Vec3X<T> const & lhs, Vec3X<T> const & rhs);
    // Vec3X<T> operator / (Vec3X<T> const & lhs, Vec3X<T> const & rhs);

    // Vec3X<T> operator + (T lhs, Vec3X<T> const & rhs);
    // Vec3X<T> operator - (T lhs, Vec3X<T> const & rhs);
    // Vec3X<T> operator * (T lhs, Vec3X<T> const & rhs);
    // Vec3X<T> operator / (T lhs, Vec3X<T> const & rhs);

    // Vec3X<T> operator + (Vec3X<T> const & lhs, float rhs);
    // Vec3X<T> operator - (Vec3X<T> const & lhs, float rhs);
    // Vec3X<T> operator * (Vec3X<T> const & lhs, float rhs);
    // Vec3X<T> operator / (Vec3X<T> const & lhs, float rhs);

public: // free function operator overload for use with other classes - defined in Vec3X.inl
    // Vec3X<T> operator * (Mat3<T> const & lhs, Vec3X<T> const & rhs); - defined in Mat3.inl

public: // public data
    T x;
    T y;
    T z;
};
} /* namespace Maths */
#include "Vec3X.inl"
#endif /* Vec3X_hpp */