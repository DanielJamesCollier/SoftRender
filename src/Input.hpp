#ifndef Input_hpp
#define Input_hpp

// my
#include "Messages/Subject.hpp"
#include "Messages/ObserverInput.hpp"


// std
#include <vector>

// dependencies
#include "SDL_Events.h"
#include "SDL_Haptic.h"

class Input final : public Subject<ObserverInput> {
public:
    Input();
    ~Input();

    bool update();

    bool isLeftDown() {
        return leftDown;
    }

    bool isRightDown() {
        return rightDown;
    }

    bool isUpDown() {
        return upDown;
    }

    bool isDownDown() {
        return downDown;
    }

private:
    void addController();
    void removeController();
    void handleButton(int button, bool updown);

   

private:
    SDL_Event m_event;
    
    // controller
    SDL_GameController * m_controller;
    SDL_Joystick * m_joystick;
    SDL_Haptic * m_haptic;

    bool leftDown = false;
    bool rightDown = false;
    bool upDown = false;
    bool downDown = false;
};
#endif /* Input_hpp */
