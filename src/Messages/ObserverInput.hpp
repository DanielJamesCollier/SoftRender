#ifndef ObserverInput_hpp
#define ObserverInput_hpp

class ObserverInput {
public:

    ObserverInput() = default;
    ~ObserverInput() = default;

    /* controller */

    // joy sticks
    virtual void controllerLeftStickXEvent(float x) {

    };

    virtual void controllerLeftStickYEvent(float y) {

    };

    virtual void controllerRightStickXEvent(float x) {

    };

    virtual void controllerRightStickYEvent(float y) {

    };

    // triggers
    virtual void leftTriggerEvent(float amount) {

    }

    virtual void rightTriggerEvent(float amount) {

    }

    // buttons - includes joystick click buttons
    virtual void controllerButtonDownEvent(int button) {

    }

    virtual void controllerButtonUpEvent(int button) {

    }

    /* keyboard */ 
    // todo
};

#endif /* ObserverInput_hpp */