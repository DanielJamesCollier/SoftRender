#include <cmath>
#include <iostream>

#ifndef Vec3_hpp
#define Vec3_hpp

namespace Maths {
    class Vec3 final {
    public:
        explicit Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
        
        // getters
        float getX() const;
        float getY() const;
        float getZ() const;

        // setters
        void setX(float x);
        void setY(float y);
        void setZ(float z);

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
        

        friend Vec3 operator += (float lhs, Vec3 const & rhs);
        friend Vec3 operator -= (float lhs, Vec3 const & rhs);
        friend Vec3 operator *= (float lhs, Vec3 const & rhs);
        friend Vec3 operator /= (float lhs, Vec3 const & rhs);
        
        friend Vec3 operator + (float lhs, Vec3 const & rhs);
        friend Vec3 operator - (float lhs, Vec3 const & rhs);
        friend Vec3 operator * (float lhs, Vec3 const & rhs);
        friend Vec3 operator / (float lhs, Vec3 const & rhs);

        //@TODO DODODODODOODODODOODOOD THISSSSSSSSS
        friend Vec3 operator + (Vec3 const & lhs, float rhs);
        friend Vec3 operator - (Vec3 const & lhs, float rhs);
        friend Vec3 operator * (Vec3 const & lhs, float rhs);
        friend Vec3 operator / (Vec3 const & lhs, float rhs);
        //...

        friend Vec3 operator + (Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 operator - (Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 operator * (Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 operator / (Vec3 const & lhs, Vec3 const & rhs);

        friend float length2(Vec3 const & vec);
        friend float length(Vec3 const & vec);
        friend float distance(Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 getLongest(Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 normalise(Vec3 const & vec);
        friend float dot(Vec3 const & lhs, Vec3 const & rhs);
        friend Vec3 cross(Vec3 const & lhs, Vec3 const & rhs);

        friend std::ostream & operator << (std::ostream & lhs, Vec3 const & rhs);

    private:
        float m_data[3];
    };
    #include "Vec3.inl"
} // namespace maths
#endif // Vec3_hpp
