#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Vec4.hpp"
#include "Maths/Mat4f.hpp"

class Vertex {
    friend class RenderContext;
public:
    Vertex(float x, float y, float z);
    Vertex(Maths::Vec4 const & pos);

    Vertex transform(Maths::Mat4f & matrix) { 
        Maths::Vec4 pos = matrix * position;
        return Vertex(Maths::Vec4(pos.x, pos.y, pos.z, pos.w)); 
    }

private:
    Vertex perspectiveDivide(); // called from render context : todo : no real need to create a whole new Vertex

public:
    Maths::Vec4 position;
};
#endif /* Vertex_hpp  */