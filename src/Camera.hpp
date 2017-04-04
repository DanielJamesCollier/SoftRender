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
    void updatePerspective() {

    }

    // * observer Input virual overides *//
    void controllerAxisEvent() {

    }

    void controllerButtonDownEvent(int button) {
        std::cout << "button down" << std::endl;
    }

    void controllerButtonUpEvent(int button) {

    }

private:
    Maths::Mat4f m_projection;
    Maths::Vec3  m_position;
    Maths::Vec3  m_rotation;
    Maths::Mat4f m_transform;
};

#endif /* Camera_hpp */