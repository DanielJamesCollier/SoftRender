// std
#include <string>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

//------------------------------------------------------------
Mesh 
loadDannyFile(std::string const & filePath) {
    Mesh mesh;

    std::ifstream file(filePath);

    if(file.is_open()) {
        
        std::string str; 
        while (std::getline(file, str)) {
            std::stringstream ss(str);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> vstrings(begin, end);
        }
    }

    return mesh;
}

//------------------------------------------------------------
int main(int argc, char* argv[]) {
    
    // using
    using clock = std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using FpMilliseconds  = duration<float, milliseconds::period>;
    //..

    // window spec
    bool vSync = false;
    bool fullScreen = false;
    int width = 900;
    int height = width / 16 * 10;
    float bufferScale = 2.0f; // size of the framebuffer compared to the screen width & height
    Window window("SoftRender", -1, -1, width, height, bufferScale, vSync, fullScreen);
    //..

    Input input;
    RenderContext & rContext = window.getRenderContext();
    StarField starField(rContext, 0.00001f, 0.1);

    // triangle
    Vertex v1(Maths::Vec3(-1, -1, 0), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(1,0,0)); // bottom left
    Vertex v2(Maths::Vec3( 0,  1, 0), Maths::Vec2(0.5f, 0.0f), Maths::Vec3(0,1,0)); // top
    Vertex v3(Maths::Vec3( 1, -1, 0), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(0,0,1)); // bottom right
    //..
    
    // pyramid mesh
        std::vector<Vertex> pyramid;

        // front 
        pyramid.push_back(Vertex(Maths::Vec3(-1, -1, -1), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // left
        pyramid.push_back(Vertex(Maths::Vec3( 0,  1,  0), Maths::Vec2(0.5f, 0.0f), Maths::Vec3(0.0f, 1.0f, 0.0f))); // top
        pyramid.push_back(Vertex(Maths::Vec3( 1, -1, -1), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // right

        // back
        pyramid.push_back(Vertex(Maths::Vec3(-1, -1,  1), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // left
        pyramid.push_back(Vertex(Maths::Vec3( 0,  1,  0), Maths::Vec2(0.5f, 0.0f), Maths::Vec3(0.0f, 1.0f, 0.0f))); // top
        pyramid.push_back(Vertex(Maths::Vec3( 1, -1,  1), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // right

        // left
        pyramid.push_back(Vertex(Maths::Vec3(-1, -1, -1), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // left
        pyramid.push_back(Vertex(Maths::Vec3( 0,  1,  0), Maths::Vec2(0.5f, 0.0f), Maths::Vec3(0.0f, 1.0f, 0.0f))); // top
        pyramid.push_back(Vertex(Maths::Vec3(-1, -1,  1), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // right

        // right
        pyramid.push_back(Vertex(Maths::Vec3(1, -1, -1), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // left
        pyramid.push_back(Vertex(Maths::Vec3(0,  1,  0), Maths::Vec2(0.5f, 0.0f), Maths::Vec3(0.0f, 1.0f, 0.0f))); // top
        pyramid.push_back(Vertex(Maths::Vec3(1, -1,  1), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // right
    //..

    // cube - indexed mesh
    std::vector<Vertex> cube;

    // front square
    cube.push_back(Vertex(Maths::Vec3(-1, -1,  1), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // bottom left  // 0
    cube.push_back(Vertex(Maths::Vec3(-1,  1,  1), Maths::Vec2(0.0f, 0.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // top left     // 1
    cube.push_back(Vertex(Maths::Vec3( 1,  1,  1), Maths::Vec2(1.0f, 0.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // top right    // 2
    cube.push_back(Vertex(Maths::Vec3( 1, -1,  1), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // bottom right // 3

    // back square
    cube.push_back(Vertex(Maths::Vec3(-1, -1, -1), Maths::Vec2(1.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // bottom left  // 4
    cube.push_back(Vertex(Maths::Vec3(-1,  1, -1), Maths::Vec2(1.0f, 0.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // top left     // 5
    cube.push_back(Vertex(Maths::Vec3( 1,  1, -1), Maths::Vec2(0.0f, 0.0f), Maths::Vec3(0.0f, 0.0f, 1.0f))); // top right    // 6
    cube.push_back(Vertex(Maths::Vec3( 1, -1, -1), Maths::Vec2(0.0f, 1.0f), Maths::Vec3(1.0f, 0.0f, 0.0f))); // bottom right // 7

    std::vector<unsigned int> cubeIndices;

   
    cubeIndices.push_back(7); // 1.0, 1.0
    cubeIndices.push_back(3); // 1.0, 1.0
    cubeIndices.push_back(0); // 0.0, 1.0
    

    // // front
    // {
    //      // front - top left tri
    //     cubeIndices.push_back(0);
    //     cubeIndices.push_back(1);
    //     cubeIndices.push_back(2);

    //     // front - bot right tri
    //     cubeIndices.push_back(2);
    //     cubeIndices.push_back(3);
    //     cubeIndices.push_back(0);
    // }
       
    // // back 
    // {
    //     cubeIndices.push_back(4);
    //     cubeIndices.push_back(5);
    //     cubeIndices.push_back(6);

    //     // back - top right tri
    //     cubeIndices.push_back(6);
    //     cubeIndices.push_back(7);
    //     cubeIndices.push_back(4);
    // }

    //  // top
    // {
    //     cubeIndices.push_back(1);
    //     cubeIndices.push_back(5);
    //     cubeIndices.push_back(6);

    //     // back - top right tri
    //     cubeIndices.push_back(6);
    //     cubeIndices.push_back(2);
    //     cubeIndices.push_back(1);
    // }

    //  // bottom
    // {
    //     cubeIndices.push_back(0);
    //     cubeIndices.push_back(4);
    //     cubeIndices.push_back(7);

    //     // back - top right tri
    //     cubeIndices.push_back(7);
    //     cubeIndices.push_back(3);
    //     cubeIndices.push_back(0);
    // }
    
    //..

    Bitmap randomBitmap = createRandomBitmap(100, 100);

    //  tree loaded from danny file
    Mesh mesh = loadDannyFile("../../res/mesh.danny");
    
    // game loop vars
    auto frames = 0;
    auto begin = clock::now();
    auto second = clock::now();
    //..

    float x = 0.0f;
    float z = -3.0f;

    // matricies
    Maths::Mat4f translation = Maths::createTranslationMatrix(Maths::Vec3(x, 0, z)); 
    Maths::Mat4f rotation    = Maths::createRotationMatrix(Maths::Vec3(0.0f));
    Maths::Mat4f scale       = Maths::createScaleMatrix(Maths::Vec3(1.0f));
    Maths::Mat4f proj        = Maths::createProjectionMatrix(Maths::toRadians(80.0f), 0.01f, 1000.0f, (float)width / (float)height);
    //..

    // incrementers
    float rot = 0.0f;
    //..

    while(true) {
        if(!input.update()) break;
        frames++;

        auto current = clock::now();
        float delta = FpMilliseconds(current - begin).count();
        begin = clock::now();

        // update
        starField.update(delta);
        rotation = Maths::createRotationMatrix(Maths::Vec3(0, rot, 0));
        rot += 0.0005f * delta;

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

        // render
        window.clear();
        rContext.clearDepthBuffer();
        {
            starField.render();
            rContext.drawMesh(pyramid, model, randomBitmap);
            //rContext.drawMesh(cube, cubeIndices, model, randomBitmap);
        }
        window.swapBackBuffer();
    }
    return 0;
}