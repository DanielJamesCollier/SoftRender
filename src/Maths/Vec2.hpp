#ifndef Vec2_hpp
#define Vec2_hpp

#include <iostream>

namespace Maths {

class Vec2 final {
public:
    explicit Vec2(float _x = 0, float _y = 0);
    ~Vec2() = default;

    // vector exlusive operations
    float length() const;
    float length2() const;
    void normalise();
    float dot(Vec2 const & vec) const;

    // unary opps
    Vec2   operator + () const;
    Vec2   operator - () const;
    
    // maths operators -  ((non const this, const vec) || (non const this, float scalar)
    Vec2   operator + (Vec2 const & vec);
    Vec2   operator - (Vec2 const & vec);
    Vec2   operator * (Vec2 const & vec);
    Vec2   operator / (Vec2 const & vec);
    Vec2   operator + (float scalar);
    Vec2   operator - (float scalar);
    Vec2   operator * (float scalar);
    Vec2   operator / (float scalar);

    // assignment operators (Vec3 [operator] Vec3)
    Vec2 & operator += (Vec2 const & vec);
    Vec2 & operator -= (Vec2 const & vec);
    Vec2 & operator *= (Vec2 const & vec);
    Vec2 & operator /= (Vec2 const & vec);
    Vec2 & operator += (float scalar);
    Vec2 & operator -= (float scalar);
    Vec2 & operator *= (float scalar);
    Vec2 & operator /= (float scalar);

    float x, y;
};

} /* namespace Maths */
#include "Vec2.inl"
#endif /* Vec2_hpp */