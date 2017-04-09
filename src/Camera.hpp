#ifndef Camera_hpp
#define Camera_hpp

#include "djc_math/djc_math.hpp"
#include "Input.hpp"
#include "Messages/ObserverInput.hpp"
#include <iostream>

class Camera : public ObserverInput {
public:
    Camera(float fov, float near, float far, float aspect) 
    :   m_projection(djc_math::createMat4ProjectionMatrix(djc_math::toRadians(fov), aspect, near, far))
    ,   m_view()
    ,   m_viewDirection(0.0f, 0.0f, -1.0f)
    ,   m_up(0.0f, 1.0, 0.0f)
    ,   m_position(0.0f)
    ,   m_update(true)
    {
        // empty
    }

    djc_math::Mat4f getViewProjection() {

        if(m_update) {

           // m_viewDirection = djc_math::rotate(0.0001f, m_up) * m_viewDirection;

            m_view = djc_math::createMat4ViewMatrix(m_position, m_position + m_viewDirection, m_up);

            m_update = false;

            std::cout << "view: " << m_view << std::endl;
        }

        return m_projection * m_view;
    }

    // the window was resized ? or just want to change fov ?: todo
    void updatePerspective() {}

    // * observer Input virual overides *//
    void controllerButtonDownEvent(int button) {
      
    }

    void controllerButtonUpEvent(int button) {
   
    }

    void controllerLeftStickXEvent(float x) {

    };

    void controllerLeftStickYEvent(float y) {

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
    djc_math::Mat4f m_projection;
    djc_math::Mat4f m_view;
    djc_math::Vec3f m_viewDirection;
    djc_math::Vec3f m_up;
    djc_math::Vec3f m_position;

    bool m_update;
};

#endif /* Camera_hpp */