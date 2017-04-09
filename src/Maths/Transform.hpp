#ifndef Transform_hpp
#define Transform_hpp

// std
#include <array>
#include <cmath>

// my
#include "Vec3.hpp"
#include "Mat3.hpp"
#include "Mat4.hpp"

namespace djc_math {

//-----------------//
/*      Mat3       */
//-----------------//

// create new //

template<typename T> inline Mat3<T>
createMat3IdentityMatrix();

template<typename T> inline Mat3<T>
createMat3RotationMatrix(Vec3<T> const & vec);

// use existing //

//-------------------//
/*      Mat4        */
//-------------------//

// create new //

template<typename T> inline Mat4<T> 
createMat4IdentityMatrix();

template<typename T> inline Mat4<T>
createMat4TranslationMatrix(Vec3<T> const & vec);

template<typename T> inline Mat4<T>
createMat4RotationMatrix(Vec3<T> const & vec);

template<typename T> inline Mat4<T>
createMat4ScaleMatrix(Vec3<T> const & vec);

template<typename T> inline Mat4<T>
createMat4ModelMatrix(Vec3<T> const & position, Vec3<T> const & rotation, Vec3<T> const & scale);

template<typename T> inline Mat4<T>
createMat4ProjectionMatrix(T fov, T near, T far, T aspect);

template<typename T> inline Mat4<T>
createMat4ScreenSpaceTransform(T halfWifth, T halfHeight);

// use existing
template<typename T> inline void 
setMat4Identity(Mat4<T> & matrix);

} /* namespace djc_math */
#include "inline/Transform.inl"
#endif /* Transform_hpp */

