#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Mat4f.hpp"

class Mat4f;

class Vertex {
    friend class RenderContext;
public:
    Vertex(float x, float y, float z);
    Vertex(Maths::Vec4 const & pos);

    Vertex transform(Maths::Mat4f & matrix);

    // helper funcs
    float getX() {
        return position.x;
    }

    float getY() {
        return position.y;
    }

private:
    Vertex perspectiveDivide(); // called from render context : todo : no real need to create a whole new Vertex
    float triangleAreaTimesTwo(Vertex const & b, Vertex const & c);
public:
    Maths::Vec4 position;
};
#endif /* Vertex_hpp  */