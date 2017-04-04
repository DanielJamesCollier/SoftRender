#ifndef ObserverInput_hpp
#define ObserverInput_hpp

class ObserverInput {
public:

    ObserverInput() = default;
    ~ObserverInput() = default;

    virtual void controllerAxisEvent() {

    };

    virtual void controllerButtonDownEvent(int button) {

    }

    virtual void controllerButtonUpEvent(int button) {

    }
};

#endif /* ObserverInput_hpp */