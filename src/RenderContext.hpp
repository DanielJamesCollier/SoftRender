#ifndef RenderContext_hpp
#define RenderContext_hpp

// std
#include <vector>

// my
#include "Bitmap.hpp" 
#include "Vertex.hpp"
#include "djc_math/Mat4.hpp"

class Edge;

class RenderContext : public Bitmap {
    friend class Window;
public:
    RenderContext(int width, int height);
    virtual ~RenderContext() = default;

   
    /*
        drawTriangle(...)

        - vertices can be outside of the screen
        - if vertices are outside of the screen they will be clipped
    */
    void drawTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap); 

    /*
        drawMesh(...)

        - draw mesh takes a std::vector of vertices. all vertices bust be in order
        - if there is repeating vertex data it is preferable to use drawIndexMesh
        - all vertices that go outside of the screen bounds will be clipped
    */
    void drawMesh(std::vector<Vertex> vertices, djc_math::Mat4f & transform, Bitmap & bitmap); 

    /*
        drawIndexedMes(...)

        - prefer this function over drawMesh(...) when there is repeating vertex data
        - all vertices that go outside of the screen bounds will be clipped
    */
    void drawIndexedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> const & indices, djc_math::Mat4f const & transform, Bitmap & bitmap); 
    
    /* 
        clearDepthBuffer()

        - clears the depth buffer if depth buffering is enabled -> todo
    */
    void clearDepthBuffer();

private:
    /*
        drawTriangleWithinScreenBounds(...)

        - undefined behavior if a vertex is outside of the screen bounds
    */
    void drawTriangleWithinScreenBounds(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap);
   
    /*
        scanTriangle(...)

        - scan triangle handles all the different types of triangles, these include
        - left handed (midY vertex is on the right)
        - right handed (midY vertex is on the left)

        - undefined behaviour if a vertex is outside of screen bounds
    */
    void scanTriangle(Vertex const & minY, Vertex const & midY, Vertex const & maxY, bool isleftHanded, Bitmap & bitmap);
    
     /*
        drawScanLine(...)

        - scan triangle handles all the different types of triangles, these include
        - left handed (midY vertex is on the right)
        - right handed (midY vertex is on the left)

        - undefined behaviour if a edge start or end is outside of screen bounds
    */
    void drawScanLine(Edge const & left, Edge const & right, int y, Bitmap & bitmap);

    /*
        updateContextSize(...)

        - handles updating the back buffer size
        - handles updating the screen space transform
    */
    void updateContextSize(float width, float height); // todo : call from window when it gets resized

private:
    djc_math::Mat4f m_screenSpaceTransform;
    std::vector<float> m_depthBuffer;

    float m_halfWidth;
    float m_halfHeight;
};
#endif /* RenderContext_hpp */