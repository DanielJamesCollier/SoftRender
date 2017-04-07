#ifndef MathsTest_hpp
#define MathsTest_hpp

// std
#include <iostream>

// my
#include "Maths.hpp"

#include "template/Vec2X.hpp"
#include "template/Vec3X.hpp"

namespace Maths {

inline void testMatricies() {
    // todo : remove Matrix ending from create funtions

    std::cout << "//// MATHS TESTS ////" << std::endl;
    std::cout << "\n-----------------------------------------------------------\n" << std::endl;
    /// MATRIX 3 TESTS //// 
    ///////////////////////////////////////////////////////////////////////
    Mat3<float> mat_default;
    auto mat_rotation = Maths::createMat3RotationMatrix<float>(Maths::Vec3(1.0f));
    auto mat_identity = Maths::createMat3IdentityMatrix<float>();

    std::cout << "default: " << mat_default << std::endl;
    std::cout << "rot: " << mat_rotation << std::endl;
    std::cout << "idendity: " << mat_identity * mat_identity << std::endl;
    ///////////////////////////////////////////////////////////////////////

    std::cout << "\n-----------------------------------------------------------\n" << std::endl;

    /// MATRIX 4f ///
    ///////////////////////////////////////////////////////////////////////
    Mat4f mat4f_default;
    auto mat4f_identity    = Maths::createIdentityMatrix();
    auto mat4f_translation = Maths::createTranslationMatrix(Maths::Vec3(0.0f));
    auto mat4f_rotation    = Maths::createRotationMatrix(Maths::Vec3(1.0f));
    auto mat4f_scale       = Maths::createScaleMatrix(Maths::Vec3(1.0f));
    auto mat4f_model       = Maths::createModelMatrix(Vec3(0.0f), Vec3(0.0f), Vec3(1.0));
    auto mat4f_projection   = Maths::createProjectionMatrix(70.0f, 0.001f, 1000.0f, 900.0f / 600.0f);

    std::cout << "default:     " << mat4f_default << std::endl;
    std::cout << "identity:    " << mat4f_identity * mat4f_identity << std::endl;
    std::cout << "translation: " << mat4f_translation << std::endl;
    std::cout << "rotation:    " << mat4f_rotation << std::endl;
    std::cout << "scale:       " << mat4f_scale << std::endl;
    std::cout << "model:       " << mat4f_model << std::endl;
    std::cout << "projection:  " << mat4f_projection << std::endl;
    ///////////////////////////////////////////////////////////////////////

    std::cout << "\n-----------------------------------------------------------\n" << std::endl;

    /// MATRIX 4 ///
    ///////////////////////////////////////////////////////////////////////
    Mat4<float> mat4_default;
    auto mat4_identity    = Maths::createMat4IdentityMatrix<float>();
    auto mat4_translation = Maths::createMat4TranslationMatrix<float>(Maths::Vec3(0.0f));
    auto mat4_rotation    = Maths::createMat4RotationMatrix<float>(Maths::Vec3(1.0f));
    auto mat4_scale       = Maths::createMat4ScaleMatrix<float>(Maths::Vec3(1.0f));
    auto mat4_model       = Maths::createMat4ModelMatrix<float>(Maths::Vec3(0.0f), Maths::Vec3(0.0f), Maths::Vec3(1.0f));
    auto mat4_projection  = Maths::createMat4ProjectionMatrix<float>(70.0f, 0.001f, 1000.0f, 900.0f / 600.0f);

    std::cout << "default:     " << mat4_default << std::endl;
    std::cout << "identity:    " << mat4_identity * mat4_identity << std::endl;
    std::cout << "translation: " << mat4_translation << std::endl;
    std::cout << "rotation:    " << mat4_rotation << std::endl;
    std::cout << "scale:       " << mat4_scale << std::endl;
    std::cout << "model:       " << mat4_model << std::endl;
    std::cout << "projection:  " << mat4_projection << std::endl;
    ///////////////////////////////////////////////////////////////////////

    std::cout << "\n-----------------------------------------------------------\n" << std::endl;
    std::cout << "//// END MATHS TESTS ////" << std::endl;
}

inline void testVectors() {
    /// Vec3X ///
    ///////////////////////////////////////////////////////////////////////
    
    // default
    Vec3X<float> vec3x_default;
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