#include "Window.hpp"
#include <string>

#include "MultiArray.hpp"
#include "Vec3.hpp"

int main(int argc, char* argv[]) {

    const int x = 0;
    const int y = 0;
    const int w = 900;
    const int h = w / 16 * 9;

    Window window("SoftRender", x, y, w, h);

    MultiArray<Maths::Vec3, w, h> bitmap;

    bool running = true;
    while(running) {
        window.eventLoop(running);

        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                float rr = rand()%(256-1 + 1) + 1;
                float rg = rand()%(256-1 + 1) + 1;
                float rb = rand()%(256-1 + 1) + 1;
                bitmap(i,j) = Maths::Vec3(rr,rg,rb);
            }
    }
        window.draw(bitmap);
    }

    return 0;
}