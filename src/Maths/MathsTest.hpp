#ifndef MathsTest_hpp
#define MathsTest_hpp

// std
#include <iostream>

#include "template/MathsX.hpp"

namespace djc_math {

inline void testMatricies() {
    // todo : remove Matrix ending from create funtions

    std::cout << "//// MATHS TESTS ////" << std::endl;
    std::cout << "\n-----------------------------------------------------------\n" << std::endl;
    /// MATRIX 3 TESTS //// 
    ///////////////////////////////////////////////////////////////////////
    Mat3X<float> mat_default;
    auto mat_identity = createMat3XIdentityMatrix<float>();
    auto mat_rotation = createMat3XRotationMatrix<float>(Vec3X<float>(1.0f));

    std::cout << "default: " << mat_default << std::endl;
    std::cout << "rot: " << mat_rotation << std::endl;
    std::cout << "idendity: " << mat_identity * mat_identity << std::endl;
    ///////////////////////////////////////////////////////////////////////

    // std::cout << "\n-----------------------------------------------------------\n" << std::endl;

    // /// MATRIX 4 ///
    // ///////////////////////////////////////////////////////////////////////
    Mat4X<float> mat4_default;
    auto mat4_identity    = createMat4XIdentityMatrix<float>();
    auto mat4_translation = createMat4XTranslationMatrix<float>(Vec3X<float>(0.0f));
    auto mat4_rotation    = createMat4XRotationMatrix<float>(Vec3X<float>(1.0f));
    auto mat4_scale       = createMat4XScaleMatrix<float>(Vec3X<float>(1.0f));
    auto mat4_model       = createMat4XModelMatrix<float>(Vec3X<float>(0.0f), Vec3X<float>(0.0f), Vec3X<float>(1.0f));
    auto mat4_projection  = createMat4XProjectionMatrix<float>(70.0f, 0.001f, 1000.0f, 900.0f / 600.0f);

    std::cout << "default:     " << mat4_default << std::endl;
    std::cout << "identity:    " << mat4_identity * mat4_identity << std::endl;
    std::cout << "translation: " << mat4_translation << std::endl;
    std::cout << "rotation:    " << mat4_rotation << std::endl;
    std::cout << "scale:       " << mat4_scale << std::endl;
    std::cout << "model:       " << mat4_model << std::endl;
    std::cout << "projection:  " << mat4_projection << std::endl;
    // ///////////////////////////////////////////////////////////////////////

    std::cout << "\n-----------------------------------------------------------\n" << std::endl;
    std::cout << "//// END MATHS TESTS ////" << std::endl;
}

inline void testVectors() {
    /// Vec3X ///
    ///////////////////////////////////////////////////////////////////////
    
    // default
    Vec3X<> vec3x_default;
    Vec3X<>      vec3x_implicit;
    Vec3X<>      vec3x_custom(1.0f);

    // copy construct / move
    Vec3X<float> vec3x_assign = Vec3X<float>(1.0f);
    
    // implace assign
    Vec3X<float> vec3x_increment;
    vec3x_increment += Vec3X<float>(1.0f);
    vec3x_increment -= Vec3X<float>(1.0f);
    vec3x_increment *= Vec3X<float>(1.0f);
    vec3x_increment /= Vec3X<float>(1.0f);

    // maths
    Vec3X<> vec3x_add    = vec3x_assign + Vec3X<>(2.0f);
    Vec3X<> vec3x_min    = vec3x_assign - Vec3X<>(2.0f);
    Vec3X<> vec3x_mul    = vec3x_assign * Vec3X<>(2.0f);
    Vec3X<> vec3x_div    = vec3x_assign / Vec3X<>(2.0f);

    // scalar opps

    Vec3X<> vec3x_addF   = 1.0f + Vec3X<>(1.0f);
    Vec3X<> vec3x_minF   = 1.0f - Vec3X<>(1.0f);
    Vec3X<> vec3x_mulF   = 1.0f * Vec3X<>(1.0f);
    Vec3X<> vec3x_divF   = 1.0f / Vec3X<>(1.0f);

    Vec3X<> vec3x_addFF  = Vec3X<>(1.0f) + 1.0f;
    Vec3X<> vec3x_minFF  = Vec3X<>(1.0f) - 1.0f;
    Vec3X<> vec3x_mulFF  = Vec3X<>(1.0f) * 1.0f;
    Vec3X<> vec3x_divFF  = Vec3X<>(1.0f) / 1.0f;

    // unary
    Vec3X<> vec3x_minus  = -Vec3X<>(1.0f);
    Vec3X<> vec3x_pluss  = +Vec3X<>(-1.0f);

    ///////////////////////////////////////////////////////////////////////
}

} /* namespace Maths */
#endif /* MathsTest_hpp */