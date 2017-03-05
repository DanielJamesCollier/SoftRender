#ifndef Vec4_hpp
#define Vec4_hpp

// std
#include <iostream>

namespace Maths {

class Vec4 final {
public:
    explicit Vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 0);
    
    // todo
    // float length() const;
    // float length2() const;
    // float dot(Vec4 const & rhs);
    // Vec4 cross(Vec4 const & rhs);
    // void normalise();


    //--
    Vec4 operator + ();
    Vec4 operator - ();


    //--
    Vec4 operator + (Vec4 const & rhs);
    Vec4 operator - (Vec4 const & rhs);
    Vec4 operator * (Vec4 const & rhs);
    Vec4 operator / (Vec4 const & rhs);


    //--
    Vec4 operator + (float scalar);
    Vec4 operator - (float scalar);
    Vec4 operator * (float scalar);
    Vec4 operator / (float scalar);


    //--
    Vec4 & operator += (Vec4 const & rhs);
    Vec4 & operator -= (Vec4 const & rhs);
    Vec4 & operator *= (Vec4 const & rhs);
    Vec4 & operator /= (Vec4 const & rhs);


    //--
    Vec4 & operator += (float scalar);
    Vec4 & operator -= (float scalar);
    Vec4 & operator *= (float scalar);
    Vec4 & operator /= (float scalar);

        
    //--
    float x, y, z, w;
};

} /* namespace Maths */
#include "Vec4.inl"
#endif /* Vec4_hpp */