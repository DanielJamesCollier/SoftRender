#include "Input.hpp"
#include "SDL.h"

#include <cassert>
#include <iostream>

//---------------------------------------------------------
Input::Input() :
    m_controller(nullptr)
,   m_joystick(nullptr)
,   m_haptic(nullptr)
{
    if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "SDL_Init(SDL_INIT_GAMECONTROLLER) failed" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }

    if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) {
        std::cerr << "SDL_Init(SDL_INIT_JOYSTICK) failed" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }

    if(SDL_InitSubSystem(SDL_INIT_HAPTIC) != 0) {
        std::cerr << "SDL_Init(SDL_INIT_HAPTIC) failed" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(-1); // fix - should not crash
    }

    SDL_GameControllerAddMappingsFromFile("../../res/controler_mappings.txt");
    std::cout << "Input ctor" << std::endl;  
}

Input::~Input() {
      std::cout << "input dtor" << std::endl;    
}

//---------------------------------------------------------
bool
Input::update() {
    bool running = true;
    while(SDL_PollEvent(&m_event)) {
        switch(m_event.type) {
            case SDL_QUIT:
                running = false;
            break;

            /* CONTROLER */
            case SDL_CONTROLLERDEVICEADDED:
                addController();
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                removeController(); 
                break;

            case SDL_CONTROLLERAXISMOTION:
                //std::cout << "moved" << std::endl;
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                std::cout << "button down" << std::endl;
                handleButton(m_event.cbutton.button, true);
                break;

            case SDL_CONTROLLERBUTTONUP:
                std::cout << "button up" << std::endl;
                handleButton(m_event.cbutton.button, false);
                break;
        }
    }

    return running;
}

//---------------------------------------------------------
void
Input::addController() {
    if(nullptr == m_controller) {
         if(SDL_IsGameController(0)) {
            m_controller = SDL_GameControllerOpen(0);
            if(m_controller) {
                std::cout << "controller added" << std::endl;
                
                m_joystick = SDL_GameControllerGetJoystick(m_controller);

                if(m_joystick) {
                    std::cout << "joystick working" << std::endl;

                    m_haptic = SDL_HapticOpenFromJoystick(m_joystick);

                    if(m_haptic != nullptr) {
                        std::cout << "haptic working" << std::endl;
                    } else {
                        std::cerr << "controller does not support haptic feedback" << std::endl;
                        std::cerr << SDL_GetError() << std::endl;
                    }
                } else {
                    std::cerr << "joystick failed" << std::endl;
                    std::cerr << SDL_GetError() << std::endl;
                }
            } else {
                std::cerr << "controller failed" << std::endl;
                std::cerr << SDL_GetError() << std::endl;
            }
        }
    } else {
        std::cerr << "only one controller supported" << std::endl;
    }
}

//---------------------------------------------------------
void 
Input::removeController() { // todo
    SDL_GameControllerClose(m_controller);
    m_controller = nullptr;
    std::cout << "removed" << std::endl;
}

//---------------------------------------------------------
void
Input::handleButton(int button, bool updown) {
    switch(button) {
        case SDL_CONTROLLER_BUTTON_A:

        break;

        case SDL_CONTROLLER_BUTTON_B:

        break;

        case SDL_CONTROLLER_BUTTON_X:

        break;

        case SDL_CONTROLLER_BUTTON_Y:

        break;

        case SDL_CONTROLLER_BUTTON_BACK:

        break;

        case SDL_CONTROLLER_BUTTON_GUIDE:

        break;

        case SDL_CONTROLLER_BUTTON_START:

        break;

        case SDL_CONTROLLER_BUTTON_LEFTSTICK:
           
        break;

        case SDL_CONTROLLER_BUTTON_RIGHTSTICK:

        break;

        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:

        break;

        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:

        break;

        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            if(updown) {
                upDown = true;
            } else {
                upDown = false;
            }
        break;

        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            if(updown) {
                downDown = true;
            } else {
                downDown = false;
            }
        break;

        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            if(updown) {
                leftDown = true;
            } else {
                leftDown = false;
            }
        break;

        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            if(updown) {
                rightDown = true;
            } else {
                rightDown = false;
            }
        break;
        
        case SDL_CONTROLLER_BUTTON_INVALID:

        break;
    }
}