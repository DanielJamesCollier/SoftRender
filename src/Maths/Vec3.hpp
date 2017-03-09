#ifndef Vec3_hpp
#define Vec3_hpp

// std
#include <iostream>

namespace Maths {

class Vec3 final {
public:
    explicit Vec3(float xyz = 0.0f);
    Vec3(float _x , float _y, float _z);
    ~Vec3() = default;
    
    // vector exlusive operations
    float length() const;
    float length2() const;
    void normalise();
    float dot(Vec3 const & vec) const;
    Vec3 cross(Vec3 const & vec);

    // unary opps
    Vec3 operator + () const;
    Vec3 operator - () const;
    
    // maths operators -  ((non const this, const vec) || (non const this, float scalar)
    Vec3 operator + (Vec3 const & vec);
    Vec3 operator - (Vec3 const & vec);
    Vec3 operator * (Vec3 const & vec);
    Vec3 operator / (Vec3 const & vec);
    Vec3 operator + (float scalar);
    Vec3 operator - (float scalar);
    Vec3 operator * (float scalar);
    Vec3 operator / (float scalar);

    // assignment operators (Vec3 [operator] Vec3)
    Vec3 & operator += (Vec3 const & vec);
    Vec3 & operator -= (Vec3 const & vec);
    Vec3 & operator *= (Vec3 const & vec);
    Vec3 & operator /= (Vec3 const & vec);
    Vec3 & operator += (float scalar);
    Vec3 & operator -= (float scalar);
    Vec3 & operator *= (float scalar);
    Vec3 & operator /= (float scalar);

//public
    float x, y, z;
};

} /* namespace Maths */
#include "Vec3.inl"
#endif /* Vec3_hpp */
