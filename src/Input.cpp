// my
#include "Input.hpp"
#include "Maths/Utils.hpp"

// dependancies
#include "SDL.h" // needed for SDL_INIT_GAME_CONTROLLER - could remove somehow 

// std
#include <iostream>

//------------------------------------------------------------
Input::Input() :
    m_controller(nullptr)
{
    if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "SDL_Init(SDL_INIT_GAMECONTROLLER) failed" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }

    SDL_GameControllerAddMappingsFromFile("../../res/controler_mappings.txt");
    std::cout << "Input ctor" << std::endl;  
}

//------------------------------------------------------------
Input::~Input() {
      std::cout << "input dtor" << std::endl;    
}

//------------------------------------------------------------
bool
Input::update() {
    while(SDL_PollEvent(&m_event)) {
        switch(m_event.type) {
            case SDL_QUIT:
                return false;
                break;

            /* CONTROLER */
            case SDL_CONTROLLERDEVICEADDED:
                addController();
                break;

            case SDL_CONTROLLERDEVICEREMOVED:
                removeController(); 
                break;
            

            // need to scale m_event.caxis.value to values between -1.0 to 1.0 from vals between -32768 to 32767

            case SDL_CONTROLLERAXISMOTION:
            {
                bool inDeadZone = m_event.caxis.value > -m_joystickDeadZone && m_event.caxis.value < m_joystickDeadZone;

                float trigger = (static_cast<float>(m_event.caxis.value) + 32768.0f) / 65535.0f;
                float stick   = ((trigger * 2.0f) - 1.0f);

                if(inDeadZone) {
                    stick = 0;
                    trigger = 0;
                }
                
                switch(m_event.caxis.axis) {

                    case SDL_CONTROLLER_AXIS_LEFTX:
                        for(auto observer : m_observers) {
                            observer->controllerLeftStickXEvent(stick);
                        }
                        break;

                    case SDL_CONTROLLER_AXIS_LEFTY: 
                        for(auto observer : m_observers) {
                            observer->controllerLeftStickYEvent(stick);
                        }
                        break;  

                    case SDL_CONTROLLER_AXIS_RIGHTX:
                        for(auto observer : m_observers) {
                            observer->controllerRightStickXEvent(stick);
                        }
                        break;

                    case SDL_CONTROLLER_AXIS_RIGHTY:
                        for(auto observer : m_observers) {
                            observer->controllerRightStickYEvent(stick);
                        }
                        break;
                    
                    case SDL_CONTROLLER_AXIS_TRIGGERLEFT: 
                        for(auto observer : m_observers) {
                            observer->leftTriggerEvent(trigger);
                        }
                        break;

                    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                        for(auto observer : m_observers) {
                            observer->rightTriggerEvent(trigger);
                        }
                        break; 
                }   
                break;
            }

            case SDL_CONTROLLERBUTTONDOWN:
                for(auto observer : m_observers) {
                    observer->controllerButtonDownEvent(m_event.cbutton.button);
                }
                break;

            case SDL_CONTROLLERBUTTONUP:
                for(auto observer : m_observers) {
                    observer->controllerButtonUpEvent(m_event.cbutton.button);
                }
                break;

            /* keyboard */ // todo
        }
    }

    return true;
}

//------------------------------------------------------------
void // fix : only allow one controller
Input::addController() {

    int lotsOfJoy = SDL_NumJoysticks();
    
    std::cout << "num joysticks: " << lotsOfJoy << '\n';
    
    for(int i = 0; i < lotsOfJoy; i++) {
       if(SDL_IsGameController(i)) {
           std::cout << "joystick " << i << ": is a game controller\n";

           m_controller = SDL_GameControllerOpen(i);

           if(m_controller) {
               std::cout << "game controller opened\n";
               break;
           } else {
               std::cerr << "game controller could not be opened\n";
           }
       }
    }
}

//------------------------------------------------------------
void 
Input::removeController() { // todo
    SDL_GameControllerClose(m_controller);
    m_controller = nullptr;
    std::cout << "removed" << std::endl;
}