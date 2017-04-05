#ifndef Camera_hpp
#define Camera_hpp

#include "Maths/Maths.hpp"
#include "Input.hpp"
#include "Messages/ObserverInput.hpp"
#include <iostream>

class Camera : public ObserverInput {
public:
    Camera(float fov, float near, float far, float aspect) : 
        m_projection(Maths::createProjectionMatrix(Maths::toRadians(fov), near, far, aspect))
    ,   m_position(0.0f)
    ,   m_rotation(0.0f) {
    
    m_transform = Maths::createTranslationMatrix(m_position) *
                  Maths::createRotationMatrix(m_rotation);
    }

    Maths::Mat4f getViewProjection() const {
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
    Maths::Mat4f m_projection;
    Maths::Vec3  m_position;
    Maths::Vec3  m_rotation;
    Maths::Mat4f m_transform;

    Maths::Vec3 m_velocity;
};

#endif /* Camera_hpp */