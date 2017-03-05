#ifndef Maths_hpp
#define Maths_hpp

// c std
#include <cstdlib> 

// my
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4f.hpp"
#include "Transform.hpp"

// defines
#define PI 3.14159265359

namespace Maths {

//------------------------------------------------------------
inline constexpr float 
toRadians(float degrees) {
    return (degrees * PI) / 180;
}

//------------------------------------------------------------
inline float 
randFBetweenZeroOne() {
    return (double)rand() / ((double)RAND_MAX + 1);
}
    
} /* namespace Maths */

#endif /*Maths_hpp*/ 
