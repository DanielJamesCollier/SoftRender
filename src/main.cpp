// std
#include <string>
#include <chrono>

// my
#include "Window.hpp"
#include "RenderContext.hpp"
#include "MultiArray.hpp"
#include "Vec3.hpp"
#include "Colour.hpp"
#include "Bitmap.hpp"
#include "StarField.hpp"

int main(int argc, char* argv[]) {
    // using
    using std::chrono::system_clock;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    
    // window spec
    const int x = 10;
    const int y = 10;
    const int w = 900;
    const int h = w / 16 * 9;

    Window window("SoftRender", x, y, w, h , false);
    RenderContext & rContext = window.getRenderContext();
    StarField starField(rContext, 0.00001f,.1);

    // triangle verts
    Maths::Vec3 v1(100, 100, 0);
    Maths::Vec3 v2(150, 200, 0);
    Maths::Vec3 v3(80, 300, 0);

    auto frames = 0;
    bool running = true;
    constexpr milliseconds timestep(16);
    auto begin = system_clock::now();
    auto second = system_clock::now();
    while(running) {
        window.eventLoop(running); // check to see if the window was closed  
        
        frames++;

        auto current = system_clock::now();
        auto frameTime = current - begin;
        begin = current;

        while(duration_cast<milliseconds>(frameTime) > milliseconds(0)) {
            starField.update(16); // needs fixing
            frameTime -= timestep;
        }

        if(duration_cast<milliseconds>(current - second) > milliseconds(1000)) {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            second = current; 
        }

        rContext.scanConvertTriangle(v1, v2, v3, 0);
        rContext.fillShape(100,300);

       
        starField.render();
        window.swapBackBuffer();
    }
    return 0;
}