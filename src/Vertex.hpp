#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4f.hpp"

class Mat4f;

class Vertex {
    friend class RenderContext;
public:
    Vertex(Maths::Vec3 _position, Maths::Vec2 _texCoord = Maths::Vec2(0,0), Maths::Vec3 _colour = Maths::Vec3(1, 1, 1));
    Vertex(Maths::Vec4 const & _position, Maths::Vec2 _texCoord, Maths::Vec3 _colour);

    Vertex transform(Maths::Mat4f & matrix);

    // helper funcs
    float getX() const {
        return position.x;
    }

    float getY() const {
        return position.y;
    }
   
    Maths::Vec4 position;
    Maths::Vec2 texCoord;
    Maths::Vec3 colour;
};
#endif /* Vertex_hpp  */