#ifndef RenderContext_hpp
#define RenderContext_hpp

// my
#include "Bitmap.hpp" 
#include "Vertex.hpp"
#include "Maths/Mat4f.hpp"

class Edge;

class RenderContext : public Bitmap {
    friend class Window;
public:
    RenderContext(int width, int height);
    virtual ~RenderContext() = default;

    void fillTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap);
    void wireTriangle(Vertex v1, Vertex v2, Vertex v3);
    void drawLine(Vertex v1, Vertex v2);

private:
    void scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool handedness, Bitmap & bitmap);
    void drawScanLine(Edge left, Edge right, int y);
    void updateContextSize(float width, float height); // todo : call from window when it gets resized

private:
    Maths::Mat4f m_screenSpaceTransform;
};
#endif /* RenderContext_hpp */