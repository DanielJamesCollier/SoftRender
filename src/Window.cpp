// std
#include <iostream>

// my
#include "Window.hpp"
#include "SDL2/SDL.h"

//------------------------------------------------------------
Window::Window(std::string const & title, int x, int y, int width, int height, bool vSync, bool fullscreen) :
    m_title(title)
,   m_width(width)
,   m_height(height) 
,   m_rContext(width, height)
,   m_window(nullptr)
,   m_renderer(nullptr)
,   m_renderTexture(nullptr)
{
    // if x or y == -1 set the respected axis to centre
    if(x == -1) {
        x = SDL_WINDOWPOS_CENTERED;
    } 

    if(y == -1) {
        y = SDL_WINDOWPOS_CENTERED;
    }

    // init SDL and create window
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    // default window flags
    int windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;
    
    // if fullscreen append the flag
    if(fullscreen) {
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP; // if the bitmap is smaller than the window then it will be scaled
    }

    m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, windowFlags);
    if (m_window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }
    //..

    // create renderer
    int rendererFlags = SDL_RENDERER_ACCELERATED;

    // todo : somehow let v-sync be a runtime option 
    if(vSync) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);

    if (m_renderer == nullptr) {
        SDL_DestroyWindow(m_window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }
    //..

    // create render buffer
    m_renderTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

    if(m_renderTexture == nullptr) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        std::cerr << "Render Buffer Could not be created" << std::endl;
        SDL_Quit();
        exit(-1);
    }
    //..

    // clear the buffer to black
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
    SDL_GL_SetSwapInterval(static_cast<int>(vSync));
    //..
}

//------------------------------------------------------------
Window::~Window() {
    SDL_DestroyTexture(m_renderTexture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);    
    SDL_Quit();
    std::cout << "Window dtor" << std::endl;    
}

//------------------------------------------------------------
RenderContext &
Window::getRenderContext() {
    return m_rContext;
}

//------------------------------------------------------------
void 
Window::clear() { 
    m_rContext.clear();
}

//------------------------------------------------------------
void 
Window::swapBackBuffer() { 
    SDL_UpdateTexture(m_renderTexture, NULL, &m_rContext[0], m_width * 4);
    SDL_RenderCopy(m_renderer, m_renderTexture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}
