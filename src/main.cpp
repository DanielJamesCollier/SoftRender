#include "Window.hpp"
#include <string>
int main(int argc, char* argv[]) {

    Window window("SoftRender", 0, 10, 900, 600);

    bool running = true;
    while(running) {
        window.eventLoop(running);
    }

    return 0;
}