#ifndef Vec4_hpp
#define Vec4_hpp

// std
#include <iostream>

namespace Maths {

class Vec3;

class Vec4 final {   
public:
    explicit Vec4(float xyz = 0.0f);
    Vec4(float _x, float _y, float _z, float _w);
    Vec4(Vec3 const & vec, float w);
    
    // todo
    // float length() const;
    // float length2() const;
    // float dot(Vec4 const & rhs);
    // Vec4 cross(Vec4 const & rhs);
    // void normalise();
    Vec3 toVec3();


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


    float operator [] (int i) {
        switch(i) {
            case 0: return x; break;
            case 1: return y; break;
            case 2: return z; break;
            case 3: return w; break;
            default: return 0;
        }
    }
};

} /* namespace Maths */
#include "Vec4.inl"
#endif /* Vec4_hpp */