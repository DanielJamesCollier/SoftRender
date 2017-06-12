// std
#include <string>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

// dependancies
#include "SDL2/SDL.h"

// my
#include "Window.hpp"
#include "RenderContext.hpp"
#include "Input.hpp"
#include "djc_math/djc_math.hpp"
#include "Vertex.hpp"
#include "Camera.hpp"
#include "StarField.hpp"


//------------------------------------------------------------
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

//------------------------------------------------------------
std::vector<Mesh> 
loadDannyFile(std::string const & filePath) {
    std::vector<Mesh> meshes;

    std::ifstream file(filePath);

    auto stringToVec = [](std::string const & string) -> std::vector<std::string> {
        std::stringstream ss(string);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        return vstrings;
    };

    if(file.is_open()) {
        std::string line; 
        std::vector<std::string> splitLine;

        std::getline(file, line); // get the first line containing the mesh count

        splitLine = stringToVec(line); // will only contain two entries "meshCount: " + numberOfMeshes
        
        const int meshCount = std::stoi(splitLine[1]);

        int currentLineNumber = 1 + meshCount;

        struct MeshSize {
            int numVertices;
            int numIndices;
        };

        std::vector<MeshSize> meshSizes; 
        meshSizes.resize(meshCount);

        for(int currMesh = 0; currMesh < meshCount; currMesh++) {
            std::getline(file, line);
            splitLine = stringToVec(line);

            int numVertices = std::stoi(splitLine[1]);
            int numIndices  = std::stoi(splitLine[2]);

            meshSizes[currMesh].numVertices = numVertices;
            meshSizes[currMesh].numIndices = numIndices;
            
            std::cout << numVertices << " " << numIndices << std::endl;

        }
       
        std::cout << meshCount << std::endl;

       // int meshOneEndLine = currentLineNumber
       for(int i = 0; i < meshSizes.size(); i++) {
            Mesh mesh;
            
            int loopEnd = currentLineNumber + meshSizes[i].numVertices;

            // extract vertices
            for(int j = currentLineNumber; j < loopEnd; j++) {
                std::getline(file, line);
                splitLine = stringToVec(line);
                
                // extract position
                djc_math::Vec3f position;
                position.x = std::stof(splitLine[0]);
                position.y = std::stof(splitLine[1]);
                position.z = std::stof(splitLine[2]);

                // extract texture coordinates
                djc_math::Vec2f texcoord;
                texcoord.x = std::stof(splitLine[3]);
                texcoord.y = std::stof(splitLine[4]);

                // extract colours
                djc_math::Vec3f colour;
                colour.x = std::stof(splitLine[5]);
                colour.y = std::stof(splitLine[6]);
                colour.z = std::stof(splitLine[7]);

                Vertex v(position, texcoord, colour);

                mesh.vertices.push_back(v);
            }

            currentLineNumber = loopEnd;
            loopEnd += meshSizes[i].numIndices;

            // extract indices
            for(int j = currentLineNumber; j < loopEnd; j++) {
                std::getline(file, line);
                splitLine = stringToVec(line);
                mesh.indices.push_back(std::stoi(splitLine[0]));
            }
            currentLineNumber = loopEnd;

            meshes.push_back(mesh);
          
       }

        return meshes;

    } else {
        std::cerr << "file was not opened" << std::endl;
        return meshes;
    }
}

void mathTest() {
    // mat4 * mat4
    #if 0
    {
        djc_math::Mat4f one(std::array<float, 16> {{
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 8, 2, 2,
            9, 2, 5, 6
        }});

        djc_math::Mat4f two(std::array<float, 16> {{
            9, 8, 3, 5,
            6, 7, 2, 4,
            8, 4, 3, 2,
            1, 8, 5, 3
        }});

        
        djc_math::Mat4f three = one * two;

        std::cout << "\nmat4 * mat4 " << three << std::endl;
    }
    #endif

    // mat4 * vec4
    #if 0
    {
        djc_math::Mat4f m4_one = djc_math::createMat4IdentityMatrix<float>();
        djc_math::Vec4f v4_two(10, 4, 2, 8);

        std::cout << "\nmat4 * vec4 " << m4_one * v4_two << std::endl;
    }
    #endif

    // mat3 * mat3
    #if 0
    {
        // random mat3 * ranndom
        djc_math::Mat3f m3_one(std::array<float, 9>{{
            4, 6, 6,
            9, 8, 2,
            4, 9, 8,
        }});

        djc_math::Mat3f m3_two(std::array<float, 9>{{
            9, 7, 3,
            6, 5, 5,
            9, 2, 3,
        }});

        std::cout << "\nmult " << m3_one * m3_two << std::endl;
    }
    #endif
  
    // mat3 * vec3
    #if 0
    {
        djc_math::Mat3f m3_identity = djc_math::createMat3IdentityMatrix<float>();
        djc_math::Vec3f v3(10, 2, 4);
        djc_math::Vec3f v3_same = m3_identity * v3;
        std::cout << "\nv3_same: " << v3_same << std::endl;
    }
    #endif

    // perspective test
    #if 0
    {
        float width  = 1024;
        float height = 576;
        float aspect = width / height;
        djc_math::Mat4f proj = djc_math::createMat4ProjectionMatrix(djc_math::toRadians(70.0f), aspect, 0.1f, 1000.0f);

        djc_math::Vec4f point(-1.0f, -1.0f, 0.0f, 1);
        std::cout << "start: " << point << std::endl;

        djc_math::Vec4f projPoint  = proj * point;
        std::cout << "proj point: " << projPoint << std::endl;

        djc_math::Vec3f screenScale;

        djc_math::Vec3f final(projPoint.x / projPoint.w,
                              projPoint.y / projPoint.w,
                              projPoint.z / projPoint.w);

        std::cout << "div point: " << final << std::endl;                           

    }
    #endif

    // pipeline test
    {

        auto vector4TripThroughPipeline = [](djc_math::Vec4f vec) {
            std::cout << "Pipeline Test\n-------------------------\n";
            float width  = 1024;
            float height = 576;
            float aspectRatio = width / height;
            /* LOCAL SPACE */
            //------------------------------
            djc_math::Vec4f point_localSpace = vec;
            std::cout << "local space: " << point_localSpace << std::endl;
            //------------------------------

            // LOCAL -> CLIP SPACE
            //------------------------------
            djc_math::Mat4f projectionMatrix = djc_math::createMat4ProjectionMatrix(djc_math::toRadians(70.0f), aspectRatio, 0.1f, 1000.0f);
            djc_math::Vec4f point_clipSpace = projectionMatrix * point_localSpace;
            std::cout << "clip space: " << point_clipSpace << std::endl;
            //------------------------------

            // CLIP SPACE -> NORMALISED DEVICE SPACE (NDC)
            //------------------------------
            djc_math::Vec4f point_ndcSpace(point_clipSpace.x / point_clipSpace.w,
                                        point_clipSpace.y / point_clipSpace.w,
                                        point_clipSpace.z / point_clipSpace.w,
                                        point_clipSpace.w);

            std::cout << "ndc space: " << point_ndcSpace << std::endl;                                       
            //------------------------------

            // NORMALISED DEVICE SPACE -> SCREEN SPACE
            //------------------------------
            djc_math::Vec4f point_screenSpace((point_ndcSpace.x + 1) * (width / 2),
                                              (point_ndcSpace.y + 1) * (height / 2),
                                               point_ndcSpace.z,
                                               point_ndcSpace.w);

            std::cout << "screen space: " << point_screenSpace << std::endl;                         
            //------------------------------
            std::cout << "-------------------------\n";
        };
       
        float z = -3.0f;

        vector4TripThroughPipeline(djc_math::Vec4f(-1.0f, -1.0f, z, 1.0f));
        vector4TripThroughPipeline(djc_math::Vec4f( 0.0f,  1.0f, z, 1.0f));
        vector4TripThroughPipeline(djc_math::Vec4f( 1.0f, -1.0f, z, 1.0f));
    }


}

//------------------------------------------------------------
int main(int argc, char* argv[]) {

    // using
    using clock = std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using FpMilliseconds = duration<float, milliseconds::period>;
    //..

    mathTest();

    // window spec
    bool  vSync = true;
    bool  fullScreen = false;
    int   width = 1024;
    int   height = 576;
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    std::cout << "aspect " << aspect << std::endl;
    Window window("SoftRender", -1, -1, width, height, vSync, fullScreen);
    //..

    Input input; // subject
    

    RenderContext & rContext = window.getRenderContext();
    Bitmap randomBitmap = createRandomBitmap(100, 100);


    // test models
    std::vector<Mesh> tree = loadDannyFile("res/box.danny");
    
    std::vector<Vertex> triangleVerts;
    triangleVerts.push_back(Vertex(djc_math::Vec3f(-1.0f, -1.0f, 0.0f))); // bottom left
    triangleVerts.push_back(Vertex(djc_math::Vec3f( 0.0f,  1.0f, 0.0f))); // middle
    triangleVerts.push_back(Vertex(djc_math::Vec3f( 1.0f, -1.0f, 0.0f))); // bottom right

    std::vector<unsigned int> triangleIndices;
    triangleIndices.push_back(0);
    triangleIndices.push_back(1);
    triangleIndices.push_back(2);
    //
    
    // game loop vars
    auto frames = 0;
    auto begin = clock::now();
    auto second = clock::now();
    //..

    float x =  0.0f;
    float y =  0.0f;
    float z =  -3.0f;

    float movementSpeed = 0.001f;
    
    // matricies
    auto translation = djc_math::createMat4TranslationMatrix(djc_math::Vec3f(x, y, z)); 
    auto rotation    = djc_math::createMat4RotationMatrix(djc_math::Vec3f(0.0f));
    auto scale       = djc_math::createMat4ScaleMatrix(djc_math::Vec3f(1.0f));
    auto view        = djc_math::createMat4ViewMatrix(djc_math::Vec3f(-4,0, 3), djc_math::Vec3f(0), djc_math::Vec3f(0, 1,0));
    auto proj        = djc_math::createMat4ProjectionMatrix(djc_math::toRadians(70.0f), aspect, 0.1f, 1000.0f);
    //..

    // incrementers
    float rot = 0.0f;
    //..

    StarField stars(rContext, 0.001f, 0.1);

    while(true) {
        if(!input.update()) break;
        frames++;

        auto current = clock::now();
        float delta = FpMilliseconds(current - begin).count();
        begin = clock::now();

         if(input.isLeftDown()) {
             x += movementSpeed * delta;
         }
         
         translation = djc_math::createMat4TranslationMatrix(djc_math::Vec3f(x, y, z)); 

        auto viewProjection = proj * view;
        auto modelMatrix = viewProjection * translation; // * rotation * scale;
        //...
        

        // every second call this
        if(duration_cast<milliseconds>(current - second) > milliseconds(1000)) {
            std::cout << "FPS: " << frames << "\n";
            std::cout << delta << std::endl;
            frames = 0;
            second = current; 
        }
        //...

        // render
        window.clear();
        rContext.clearDepthBuffer();
        {   
            stars.update();
            stars.render();

            // for(auto i = 0; i < tree.size(); i++) {
            //     rContext.drawIndexedMesh(tree[i].vertices, tree[i].indices, modelMatrix, randomBitmap);
            // }

            
            rContext.drawIndexedMesh(triangleVerts, triangleIndices, modelMatrix, randomBitmap);
        }
        window.swapBackBuffer();
        //...
    }
}