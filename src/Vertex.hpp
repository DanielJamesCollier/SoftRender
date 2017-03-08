#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Vec3.hpp"
#include "Maths/Mat4f.hpp"
#include "Colour.hpp"

class Mat4f;

class Vertex {
    friend class RenderContext;
public:
    Vertex(Maths::Vec3 _position, Colour _colour = Colour(0, 0, 0));
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
    Colour      colour;
};
#endif /* Vertex_hpp  */