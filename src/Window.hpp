#ifndef Window_hpp
#define Window_hpp

// std
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// my 
#include "MultiArray.hpp"
#include "Maths/Vec3.hpp"
#include "Colour.hpp"
#include "RenderContext.hpp"

// dependencies
#include "SDL_Events.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Window final {
public:
    Window(std::string const & title, int x, int y, int width, int height, bool vSync);
    ~Window();

    RenderContext & getRenderContext();

    // call within a while loop - running gets set to false when program closes
    void eventLoop(bool & running);

    // draws an entire buffer - will overwrite whatever is there //todo - review
    template<int width, int height>
    void draw(MultiArray<Maths::Vec3, width, height> & pixels);

    // brings the buffer you are drawing into, into view
    void swapBackBuffer();

private:
    std::string m_title;
    SDL_Event m_event;
    RenderContext m_rContext;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Texture * m_renderTexture;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
};
#include "Window.inl"
#endif /* Window_hpp */
