#ifndef Vec4_hpp
#define Vec4_hpp

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

    //free functions
    inline Vec4 operator + (float lhs, Vec4 const & rhs) {
        return Vec4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
    }

    inline Vec4 operator - (float lhs, Vec4 const & rhs) {
        return Vec4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
    }

    inline Vec4 operator * (float lhs, Vec4 const & rhs) {
        return Vec4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
    }

    inline Vec4 operator / (float lhs, Vec4 const & rhs) {
       return Vec4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
    }

    inline std::ostream & operator << (std::ostream & lhs, Vec4 const & rhs) {
        lhs << "Vec4(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")" << std::endl;
        return lhs;
    }

} /* Maths */
#endif /* Vec4_hpp */