#ifndef Window_hpp
#define Window_hpp

// std
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// my
#include "Maths/Vec3.hpp"
#include "Colour.hpp"
#include "RenderContext.hpp"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Window final {
public:
    Window(std::string const & title, int x, int y, int width, int height, bool vSync, bool fullscreen);
    ~Window();

    RenderContext & getRenderContext();

    void clear();
    void swapBackBuffer();

private:
    std::string m_title;
    RenderContext m_rContext;
    SDL_Texture * m_renderTexture;
    SDL_Renderer * m_renderer;
    SDL_Window * m_window;
    int m_width;
    int m_height;
    int m_x;
    int m_y;
};
#endif /* Window_hpp */
