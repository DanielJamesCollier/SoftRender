#ifndef RenderContext_hpp
#define RenderContext_hpp

//std
#include <vector>
#include <iostream>

// my
#include "Vertex.hpp"
#include "Bitmap.hpp" 
#include "Maths/Mat4f.hpp"


class RenderContext : public Bitmap {
    friend class Window;
public:
    RenderContext(int width, int height);
    virtual ~RenderContext()  {
          std::cout << "RenderContext dtor" << std::endl;    
    }

    void drawScanBuffer(int y, int xMin, int xMax);
    void fillShape(int yMin, int yMax);
    void fillTriangle(Vertex v1, Vertex v2, Vertex v3);
    void scanConvertTriangle(Maths::Vec4 const & minY, Maths::Vec4 const & midY, Maths::Vec4 const & maxY, int handedness);

private:
    void scanConvertLine(Maths::Vec4 const & minY, Maths::Vec4 const &maxY, int handedness);
    void updateContextSize(float width, float height); // todo : call from window when it gets resized

private:
    std::vector<int> m_scanBuffer;
    Maths::Mat4f m_screenSpaceTransform;
};
#endif /* RenderContext_hpp */