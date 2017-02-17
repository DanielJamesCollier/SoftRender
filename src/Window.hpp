#ifndef Window_hpp
#define Window_hpp

// std
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// my 
#if defined(_WIN32)
#   include "SDL.h"
#elif defined(__APPLE__)
#   include "SDL.h"
#else
#   error "system not supported"
#endif

#include "MultiArray.hpp"
#include "Vec3.hpp"
#include "Colour.hpp"
#include "Bitmap.hpp"

class Window final {
public:
    Window(std::string const & title, int x, int y, int width, int height, bool vSync);
    ~Window();

    Bitmap & getBitmap();

    // call within a while loop - running gets set to false when program closes
    void eventLoop(bool & running);

    // draws an entire buffer - will overwrite whatever is there //todo - review
    template<int width, int height>
    void draw(MultiArray<Maths::Vec3, width, height> & pixels);

    // brings the buffer you are drawing into, into view
    void swapBackBuffer();

private:
    std::string m_title;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Event m_event;
    SDL_Texture * m_renderTexture;
    Bitmap m_pixels;
    bool m_vSync;
};
#include "Window.inl"
#endif /* Window_hpp */
