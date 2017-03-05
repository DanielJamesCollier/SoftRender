#ifndef Maths_hpp
#define Maths_hpp

#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4f.hpp"
#include "Transform.hpp"

#define PI 3.14159265359

namespace Maths {

    constexpr float toRadians(float degrees) {
        return (degrees * PI) / 180 ;
    }
    
}

#endif /*Maths_hpp*/ 
