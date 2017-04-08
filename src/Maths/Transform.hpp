#ifndef Transform_hpp
#define Transform_hpp

// my
#include "Vec4.hpp"
#include "Vec3.hpp"
#include "Mat4f.hpp"

namespace Maths {

//-------------------
/*      Mat4f       */
//-------------------

// creates new Mat4
//------------------------------------------------------------
inline Mat4f
createIdentityMatrix();

inline Mat4f 
createProjectionMatrix(float fov, float near, float far, float aspect);

inline Mat4f 
createModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale);

inline Mat4f
createTranslationMatrix(Vec3 const & position);

inline Mat4f
createRotationMatrix(Vec3 const & rotation);

inline Mat4f
createScaleMatrix(Vec3 const & scale);

inline Mat4f
createScreenSpaceTransform(float halfWidth, float halfHeight);

// operatres on existing Mat4f
//--------------------------------------------------------------
inline void 
transform(Vec4 & position, Mat4f & transformation);

inline void 
setIdentity(Mat4f & matrix);

inline void
setTranslation(Mat4f & matrix, Vec3 const & position);

inline void
setRotationX(Mat4f & matrix, float angle);

inline void
setRotationY(Mat4f & matrix, float angle);

inline void
setRotationZ(Mat4f & matrix, float angle);

inline void 
setScale(Mat4f & matrix, Vec3 const & scale);

/* Vec4 */
//-------------------
inline void
perspectiveDivide(Vec4 & vec);



} /* namespace Maths */
#include "Transform.inl"
#endif /* Transform_hpp */