#ifndef Window_hpp
#define Window_hpp

// std
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#if defined(_WIN32)
#   include "SDL.h"
#elif defined(__APPLE__)
#   include "../build/Mac/dependencies/SDL2.framework/Versions/A/Headers/SDL.h" // todo fix this mess
#else
#   error "system not supported"
#endif

#include "MultiArray.hpp"
#include "Vec3.hpp"

class Window final {
public:
    Window(std::string const & title, int x, int y, int width, int height);
    ~Window();

    void eventLoop(bool & running);

    template<int width, int height>
    void draw(MultiArray<Maths::Vec3, width, height> & pixels, int numSamples);

//TODO: reorder
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
    std::vector<unsigned char> m_pixels;
};
#include "Window.inl"
#endif /* Window_hpp */
