#ifndef Maths_hpp
#define Maths_hpp

#include "Vec3.hpp"
#include "Mat4f.hpp"

/*
    todo 
    -   add vec4
    - if maths isnt included then these operators wont work ?

*/
namespace Maths {
   
   //------------------------------------------------------------
    inline Vec3 // treats the mat4f like it is a mat3f
    operator * (Mat4f const & lhs, Vec3 const & rhs) {
        Vec3 vec;

        vec.setX((lhs.m_data[0] * rhs.getX()) + (lhs.m_data[1] * rhs.getY()) + (lhs.m_data[2] * rhs.getZ()));
        vec.setY((lhs.m_data[3] * rhs.getX()) + (lhs.m_data[4] * rhs.getY()) + (lhs.m_data[5] * rhs.getZ()));
        vec.setZ((lhs.m_data[6] * rhs.getX()) + (lhs.m_data[7] * rhs.getY()) + (lhs.m_data[8] * rhs.getZ()));

        return vec;
    }

    //------------------------------------------------------------
    inline Mat4f
    operator * (Mat4f const & lhs, Mat4f const & rhs) {
        Mat4f matrix(false);

        auto offset = [](int x, int y) {
            return 4 * x + y;
        };

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                matrix.m_data[offset(x,y)] = 0;
                for (int z = 0; z < 4; z++) {
                    matrix.m_data[offset(x,y)] += lhs.m_data[offset(x,y)] * rhs.m_data[offset(x,y)];
                }
            }
        }
        return matrix;
    }
    
    //------------------------------------------------------------
    inline std::ostream &
    operator << (std::ostream & lhs, Vec3 const & rhs) {
        lhs << "Vec3([x:" << rhs.m_data[0] << "], [y: " << rhs.m_data[1] << "], [z: " << rhs.m_data[2] << "])\n";
        return lhs; 
    }

    //------------------------------------------------------------
    inline std::ostream &
    operator << (std::ostream & lhs, Mat4f const & rhs) {
        
        auto offset = [](int x, int y) {
            return 4 * x + y;
        };

        lhs << "Mat4f\n-----------------\n";
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                   lhs << "[" << rhs.m_data[offset(x,y)] << "] "; 
            }
            lhs << std::endl;
        }
        return lhs;
    }
}

#endif /* Maths_hpp */