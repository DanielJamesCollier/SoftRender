// std
#include <string>
#include <chrono>

// my
#include "Window.hpp"
#include "MultiArray.hpp"
#include "Vec3.hpp"

int main(int argc, char* argv[]) {
    // window spec
    const int x = 0;
    const int y = 0;
    const int w = 900;
    const int h = w / 16 * 9;

    // alias
    using Clock = std::chrono::system_clock;

    Window window("SoftRender", x, y, w, h);

    MultiArray<Maths::Vec3, w, h> bitmap;

    auto clock_secStart = Clock::now();
    auto frames = 0;
    auto fps = 0;
    bool running = true;
    while(running) {
        frames++;
        auto now = Clock::now();
        window.eventLoop(running);

        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                float rr = rand()%(256-1 + 1) + 1;
                float rg = rand()%(256-1 + 1) + 1;
                float rb = rand()%(256-1 + 1) + 1;
                bitmap(i,j) = Maths::Vec3(rr,rg,rb);
            }
        }
        
        auto clock_drawS = Clock::now();
        window.draw(bitmap);
        auto clock_drawE = Clock::now();

        
        // this happens every second - put all output in here
        if(std::chrono::duration_cast<std::chrono::milliseconds>(now - clock_secStart).count() > 1000) {
            // fps
            fps = frames;
            frames = 0;
            std::cout << "FPS: " << fps << std::endl;
        
            // draw time
            std::cout << "last draw time: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock_drawE - clock_drawS).count() << "ms" << std::endl;

            // reset second counter
            clock_secStart = Clock::now();
        }
    }

    return 0;
}