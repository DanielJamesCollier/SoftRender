#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4f.hpp"
#include "Colour.hpp"

class Mat4f;

class Vertex {
    friend class RenderContext;
public:
    Vertex(Maths::Vec3 _position, Maths::Vec2 _texCoord = Maths::Vec2(0,0), Colour _colour = Colour(1, 1, 1));
    Vertex(Maths::Vec4 const & _position, Maths::Vec2 _texCoord, Colour _colour);

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
    Maths::Vec2 texCoord;
    Colour      colour;
};
#endif /* Vertex_hpp  */