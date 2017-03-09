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
    virtual ~RenderContext()  {
          std::cout << "RenderContext dtor" << std::endl;    
    }  

    void fillTriangle(Vertex v1, Vertex v2, Vertex v3);
    void wireTriangle(Vertex v1, Vertex v2, Vertex v3);
    void drawLine(Vertex v1, Vertex v2);
private:
    void scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool handedness);
    void updateContextSize(float width, float height); // todo : call from window when it gets resized

private:
    Maths::Mat4f m_screenSpaceTransform;
};
#endif /* RenderContext_hpp */