// std
#include <string>
#include <chrono>

// my
#include "Window.hpp"
#include "MultiArray.hpp"
#include "Vec3.hpp"
#include "Colour.hpp"
#include "Bitmap.hpp"
#include "StarField.hpp"

int main(int argc, char* argv[]) {
    // window spec
    const int x = 10;
    const int y = 10;
    const int w = 700;
    const int h = w / 16 * 9;

    // alias
    using Clock = std::chrono::system_clock;

    Window window("SoftRender", x, y, w, h , true);
    Bitmap & bitmap = window.getBitmap();
    StarField starField(0.001f, 2);

    auto clock_secStart = Clock::now();
    auto clock_deltaStart = Clock::now();
    auto frames = 0;
    auto fps = 0;
    bool running = true;

    while(running) {
        // timing a diagonostics
        auto now = Clock::now();
        float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - clock_deltaStart).count();
        clock_deltaStart = Clock::now();
        frames++;

        // poll the event list
        window.eventLoop(running);

        // updateAndRender star field
        starField.updateAndRender(bitmap, delta);
        
        // display the last rendered frame
        auto clock_drawS = Clock::now();
        window.swapBackBuffer();
        auto clock_drawE = Clock::now();

        
        // this happens every second - put all output in here
        if(std::chrono::duration_cast<std::chrono::milliseconds>(now - clock_secStart).count() > 1000) {
            fps = frames;
            frames = 0;

            std::cout << "frame info" << std::endl;
            std::cout << "----------" << std::endl;
            std::cout << "FPS:            " << fps << std::endl;
            std::cout << "last draw time: " << std::chrono::duration_cast<std::chrono::milliseconds>(clock_drawE - clock_drawS).count() << "ms" << std::endl;
            std::cout << "\n";

            // reset second counter
            clock_secStart = Clock::now();
        }
    }
    return 0;
}