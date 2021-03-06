#ifndef Window_hpp
#define Window_hpp

// std
#include <string>
#include <vector>

// my
#include "RenderContext.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Window final {
public:
    // set x && y to -1 if you want window centred
    Window(std::string const & title, int x, int y, int width, int height, bool vSync, bool fullscreen);
    ~Window();

    RenderContext & getRenderContext();

    void clear();
    void swapBackBuffer();

private:
    std::string m_title;
    int m_width;
    int m_height;
    RenderContext m_rContext;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    SDL_Texture * m_renderTexture;    
};
#endif /* Window_hpp */
