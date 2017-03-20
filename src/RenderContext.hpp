#ifndef RenderContext_hpp
#define RenderContext_hpp

// std
#include <vector>

// my
#include "Bitmap.hpp" 
#include "Vertex.hpp"
#include "Maths/Mat4f.hpp"

class Edge;
class Gradients;
class Mat4;

class RenderContext : public Bitmap {
    friend class Window;
public:
    RenderContext(int width, int height);
    virtual ~RenderContext() = default;

   
    void fillTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap);
    void wireTriangle(Vertex v1, Vertex v2, Vertex v3);
    void drawLine(Vertex v1, Vertex v2);
    void drawMesh(std::vector<Vertex> mesh, Maths::Mat4f & transform, Bitmap & bitmap);

private:
    void scanTriangle(Vertex const & minY, Vertex const & midY, Vertex const & maxY, bool isleftHanded, Bitmap & bitmap);
    void drawScanLine(Edge const & left, Edge const & right, int y, Bitmap & bitmap);

    void updateContextSize(float width, float height); // todo : call from window when it gets resized

private:
    Maths::Mat4f m_screenSpaceTransform;
    std::vector<float> m_depthBuffer;
};
#endif /* RenderContext_hpp */