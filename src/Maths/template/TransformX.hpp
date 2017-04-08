#ifndef TransformX_hpp
#define TransformX_hpp

// std
#include <array>
#include <cmath>

// my
#include "Vec3X.hpp"
#include "Mat3X.hpp"
#include "Mat4X.hpp"

namespace djc_math {

//-----------------//
/*      Mat3X       */
//-----------------//

// create new //

template<typename T> inline Mat3X<T>
createMat3XIdentityMatrix();

template<typename T> inline Mat3X<T>
createMat3XRotationMatrix(Vec3X<T> const & vec);

// use existing //

//-------------------//
/*      Mat4X        */
//-------------------//

// create new //

template<typename T> inline Mat4X<T> 
createMat4XIdentityMatrix();

template<typename T> inline Mat4X<T>
createMat4XTranslationMatrix(Vec3X<T> const & vec);

template<typename T> inline Mat4X<T>
createMat4XRotationMatrix(Vec3X<T> const & vec);

template<typename T> inline Mat4X<T>
createMat4XScaleMatrix(Vec3X<T> const & vec);

template<typename T> inline Mat4X<T>
createMat4XModelMatrix(Vec3X<T> const & position, Vec3X<T> const & rotation, Vec3X<T> const & scale);

template<typename T> inline Mat4X<T>
createMat4XProjectionMatrix(float fov, float near, float far, float aspect);

template<typename T> inline Mat4X<T>
createMat4XScreenSpaceTransform(float halfWifth, float halfHeight);

// use existing
template<typename T> inline void 
setMat4XIdentity(Mat4X<T> & matrix);

} /* namespace djc_math */
#include "inline/TransformX.inl"
#endif /* TransformX_hpp */

