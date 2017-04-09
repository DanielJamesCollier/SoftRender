#ifndef Camera_hpp
#define Camera_hpp

#include "Maths/djc_math.hpp"
#include "Input.hpp"
#include "Messages/ObserverInput.hpp"
#include <iostream>

class Camera : public ObserverInput {
public:
    Camera(float fov, float near, float far, float aspect) : 
        m_projection(djc_math::createMat4ProjectionMatrix<float>(djc_math::toRadians(fov), near, far, aspect))
    ,   m_position(0.0f)
    ,   m_rotation(0.0f) {
    
    m_transform = djc_math::createMat4TranslationMatrix<float>(m_position) *
                  djc_math::createMat4RotationMatrix<float>(m_rotation);
    }

    djc_math::Mat4<float> getViewProjection() const {
        return m_projection * m_transform;
    }

    // the window was resized ? or just want to change fov ?: todo
    void updatePerspective() {}

    // * observer Input virual overides *//
    void controllerButtonDownEvent(int button) {
      
    }

    void controllerButtonUpEvent(int button) {
   
    }

    void controllerLeftStickXEvent(float x) {
        m_velocity.x = x;
    };

    void controllerLeftStickYEvent(float y) {
         m_velocity.z = y;
    };

    void controllerRightStickXEvent(float x) {
        
    };

    void controllerRightStickYEvent(float y) {
       
    };

    void leftTriggerEvent(float amount) {
      
    }

    void rightTriggerEvent(float amount) {
       
    }

private:
    djc_math::Mat4<float>  m_projection;
    djc_math::Vec3<float>  m_position;
    djc_math::Vec3<float>  m_rotation;
    djc_math::Mat4<float>  m_transform;
    djc_math::Vec3<float>  m_velocity;
};

#endif /* Camera_hpp */