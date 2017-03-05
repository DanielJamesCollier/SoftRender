// std
#include <string>
#include <chrono>

// my
#include "Window.hpp"
#include "RenderContext.hpp"
#include "Colour.hpp"
#include "Bitmap.hpp"
#include "StarField.hpp"
#include "Input.hpp"

#include "Maths/Maths.hpp"
#include "Vertex.hpp"

#include "SDL.h"
// seems to crash when triangle is outside of window when program closed
// seems to crash when the triangle and or vertex is behind the camera

// translation doesnt seem to work 

int main(int argc, char* argv[]) {
    // using
    using std::chrono::system_clock;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    //..

    // window spec
    bool vSync = false;
    bool fullScreen = false;
    int width = 900;
    int height = width / 16 * 9;
    Window window("SoftRender", 10, 10, width, height, vSync, fullScreen);
    //..

    Input input;
    RenderContext & rContext = window.getRenderContext();
    StarField starField(rContext, 0.00001f,.1);

    // triangle
    Vertex v1(-1, -1, 0);
    Vertex v2(0, 1, 0);
    Vertex v3(1, -1, 0);
    //..
    
    // game loop vars
    auto frames = 0;
    bool running = true;
    constexpr milliseconds timestep(16);
    auto begin = system_clock::now();
    auto second = system_clock::now();
    //..

    float x = 0.0f;
    float z = -3.0f;

    // matricies
    Maths::Mat4f translation = Maths::createTranslationMatrix(Maths::Vec3(0, 0, z)); 
    Maths::Mat4f rotation    = Maths::createRotationMatrix(Maths::Vec3(0,0,0));
    Maths::Mat4f scale       = Maths::createScaleMatrix(Maths::Vec3(1, 1, 1));
    Maths::Mat4f proj        = Maths::createProjectionMatrix(Maths::toRadians(80.0f), 0.01f, 1000.0f, (float)width / (float)height);
    //..

    // incrementers
    float temp = 0.0001f;
    float rot = 0;
    //..


    while(true) {
        if(!input.update()) {
            break;
        }
        
        frames++;

        auto current = system_clock::now();
        auto frameTime = current - begin;
        begin = current;

        while(duration_cast<milliseconds>(frameTime) > milliseconds(0)) {
            starField.update(16); // todo : needs fixing : fix my timestep
            
            rotation = Maths::createRotationMatrix(Maths::Vec3(0,rot,0));
            //scale = Maths::createScaleMatrix(Maths::Vec3(temp, temp, temp));
                    
            frameTime -= timestep;
        }

        temp+= .0001f;
        rot += 0.01f;

        if(duration_cast<milliseconds>(current - second) > milliseconds(1000)) {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            second = current; 
        }

        window.clear();
        {
            starField.render();

            if(input.isLeftDown()) {
                x-= 0.01f;
                translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
            } else if(input.isRightDown()) {
                translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
                x+= 0.01f;
            } else if(input.isUpDown()) {
                z += -0.01f;
                translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
            } else if(input.isDownDown()) {
                translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
                z += 0.01f;
            }

            Maths::Mat4f model = proj * translation * rotation * scale;

            rContext.fillTriangle(v1.transform(model), v2.transform(model), v3.transform(model));
        }
        window.swapBackBuffer();
    }
  
    return 0;
}