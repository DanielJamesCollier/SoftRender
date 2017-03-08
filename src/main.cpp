// std
#include <string>
#include <chrono>

// dependancies
#include "SDL.h"

// my
#include "Window.hpp"
#include "RenderContext.hpp"
#include "StarField.hpp"
#include "Input.hpp"
#include "Maths/Maths.hpp"
#include "Vertex.hpp"

//------------------------------------------------------------
int main(int argc, char* argv[]) {
    // using
    using clock = std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using intMilliseconds = duration<uint64_t, milliseconds::period>;
    using FpMilliseconds  = duration<float, milliseconds::period>;
    //..

    // window spec
    bool vSync = true;
    bool fullScreen = false;
    int width = 900;
    int height = width / 16 * 10;
    Window window("SoftRender", -1, -1, width, height, vSync, fullScreen);
    //..

    Input input;
    RenderContext & rContext = window.getRenderContext();
    StarField starField(rContext, 0.00001f,.1);

    // triangle
    Vertex v1(Maths::Vec3(-1, -1, 0));
    Vertex v2(Maths::Vec3( 0,  1, 0));
    Vertex v3(Maths::Vec3( 1, -1, 0));
    //..
    
    // game loop vars
    auto frames = 0;
    bool running = true;
    auto begin = clock::now();
    auto second = clock::now();
    //..

    float x = 2.0f;
    float z = -3.0f;

    // matricies
    Maths::Mat4f translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
    Maths::Mat4f rotation    = Maths::createRotationMatrix(Maths::Vec3(0.0f));
    Maths::Mat4f scale       = Maths::createScaleMatrix(Maths::Vec3(1.0f));
    Maths::Mat4f proj        = Maths::createProjectionMatrix(Maths::toRadians(80.0f), 0.01f, 1000.0f, (float)width / (float)height);
    //..

    // incrementers
    float temp = 0.0001f;
    float rot = 0;
    //..

    while(true) {
        if(!input.update()) break;
        frames++;

        auto current = clock::now();
        float delta = FpMilliseconds(current - begin).count();
        begin = clock::now();

        // update
        starField.update(delta);
        rotation = Maths::createRotationMatrix(Maths::Vec3(0,rot,0));
        temp+= .00001f * delta;
        rot += 0.001f * delta;

        if(input.isLeftDown()) {
            x-= 0.001f * delta;
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
        } else if(input.isRightDown()) {
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
            x+= 0.001f  * delta;
        } else if(input.isUpDown()) {
            z += -0.001f  * delta;
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
        } else if(input.isDownDown()) {
            translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
            z += 0.001f * delta;
        }

        Maths::Mat4f model = proj * translation * rotation * scale;
        //..
        

        // every second call this
        if(duration_cast<milliseconds>(current - second) > milliseconds(1000)) {
            std::cout << "FPS: " << frames << "\n";
            std::cout << delta << std::endl;
            frames = 0;
            second = current; 
        }


        // translation for wire
         Maths::Mat4f wireTrans = Maths::createTranslationMatrix(Maths::Vec3(x - 4, 0, z)); 
         Maths::Mat4f wire_model = proj * wireTrans * rotation * scale;

        // render
        window.clear();
        {
            starField.render();
            rContext.fillTriangle(v3.transform(model), v2.transform(model), v1.transform(model));
            rContext.wireTriangle(v3.transform(wire_model), v2.transform(wire_model), v1.transform(wire_model));
        }
        window.swapBackBuffer();
    }
    return 0;
}