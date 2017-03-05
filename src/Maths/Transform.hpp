#ifndef Transform_hpp
#define Transform_hpp

// my
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4f.hpp"

namespace Maths {

//------------------------------------------------------------
inline Mat4f 
createProjectionMatrix(float fov, float near, float far, float aspect) {
    Mat4f matrix;

    float range = std::tan(fov / 2.0f) * near;

    float Sx = (2 * near) / (range*aspect + range*aspect);
    float Sy = near / range;
    float Sz = -(far + near) / (far - near);
    float Pz = -(2 * far * near) / (far - near);

    matrix[0] = Sx;
    matrix[5] = Sy;
    matrix[10] = Sz;
    matrix[11] = -1;
    matrix[14] = Pz;

    return matrix;
}

//------------------------------------------------------------
inline Mat4f
createIdentityMatrix() {
    Mat4f matrix;
    matrix[0]  = 1;  
    matrix[5]  = 1; 
    matrix[10] = 1; 
    matrix[15] = 1;
    return matrix;
}

//------------------------------------------------------------
inline Mat4f 
createModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale) {
    Mat4f translationMat = createIdentityMatrix();
    translationMat[12] = position.getX();
    translationMat[13] = position.getY();
    translationMat[14] = position.getZ();

    Mat4f rotX = createIdentityMatrix();
    setRotationX(rotX, rotation.getX());
    Mat4f rotY = createIdentityMatrix();
    setRotationY(rotY, rotation.getY());
    Mat4f rotZ = createIdentityMatrix();
    setRotationZ(rotZ, rotation.getZ());

    Mat4f rotationMat(rotZ * rotY * rotX);

    Mat4f scaleMat;
    scaleMat[0]  = scale.getX();
    scaleMat[5]  = scale.getY();
    scaleMat[10] = scale.getZ();
    scaleMat[15] = 1;

    return translationMat * rotationMat * scaleMat;
}

//------------------------------------------------------------
inline Mat4f
createTranslationMatrix(Vec3 const & position) {
    Mat4f translation = createIdentityMatrix();
    translation[12] = position.getX();
    translation[13] = position.getY();
    translation[14] = position.getZ();
    return translation;
}

//------------------------------------------------------------
inline Mat4f
createRotationMatrix(Vec3 const & rotation) {
    Mat4f rotX = createIdentityMatrix(); // cleanup : make code inline
    setRotationX(rotX, rotation.getX());
    Mat4f rotY = createIdentityMatrix();
    setRotationY(rotY, rotation.getY());
    Mat4f rotZ = createIdentityMatrix();
    setRotationZ(rotZ, rotation.getZ());

    Mat4f rot = rotZ * rotY * rotX; 
    //Mat4f rot = rotX * rotY * rotZ; 

    return rot;
}

//------------------------------------------------------------
inline Mat4f
createScaleMatrix(Vec3 const & scale) {
    Mat4f scaleMat;
    scaleMat[0]  = scale.getX();
    scaleMat[5]  = scale.getY();
    scaleMat[10] = scale.getZ();
    scaleMat[15] = 1;
    return scaleMat;
}

//------------------------------------------------------------
inline Mat4f
createScreenSpaceTransform(float halfWidth, float halfHeight) {
    Mat4f screen = createIdentityMatrix();
    screen[0] =  halfWidth;
    screen[5] = -halfHeight;
    screen[12] = halfWidth;
    screen[13] = halfHeight;
    return screen;
}

// opperates on existing matrices by =
//--------------------------------------------------------------
inline void 
setIdentity(Mat4f & matrix) {
    matrix[0]  = 1;  matrix[1]  = 0;  matrix[2]  = 0;  matrix[3]  = 0;
    matrix[4]  = 0;  matrix[5]  = 1;  matrix[6]  = 0;  matrix[7]  = 0;
    matrix[8]  = 0;  matrix[9]  = 0;  matrix[10] = 1;  matrix[11] = 0;
    matrix[12] = 0;  matrix[13] = 0;  matrix[14] = 0;  matrix[15] = 1;
}

//------------------------------------------------------------
inline void
setTranslation(Mat4f & matrix, Vec3 const & position) {
    matrix[12] = position.getX();
    matrix[13] = position.getY();
    matrix[14] = position.getZ();
}

//------------------------------------------------------------
inline void
setRotationX(Mat4f & matrix, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    matrix[5]  =  cos;
    matrix[6]  =  sin;
    matrix[9]  = -sin;
    matrix[10] =  cos;
}

//------------------------------------------------------------
inline void
setRotationY(Mat4f & matrix, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    matrix[0] =  cos;
    matrix[2] = -sin;
    matrix[8] =  sin;
    matrix[10] = cos;
}

//------------------------------------------------------------
inline void
setRotationZ(Mat4f & matrix, float angle) {
    float sin = std::sin(angle);
    float cos = std::cos(angle);
    matrix[0] =  cos;
    matrix[1] =  sin;
    matrix[4] = -sin;
    matrix[5] =  cos;
}

//------------------------------------------------------------
inline void 
setScale(Mat4f & matrix, Vec3 const & scale) {
    matrix[0]  = scale.getX();
    matrix[5]  = scale.getY();
    matrix[10] = scale.getZ();
}

} /* namespace Maths */

#endif /* Transform_hpp */