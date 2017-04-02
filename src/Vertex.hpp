#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4f.hpp"
#include "Maths/MathsUtils.hpp"

class Mat4f;

class Vertex {
    friend class RenderContext;
public:
    Vertex(Maths::Vec3 _position, Maths::Vec2 _texCoord = Maths::Vec2(0,0), Maths::Vec3 _colour = Maths::Vec3(1, 1, 1));
    Vertex(Maths::Vec4 const & _position, Maths::Vec2 _texCoord, Maths::Vec3 _colour);

    Vertex transform(Maths::Mat4f & matrix);

    // fix : remove these garbage functions
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

inline Vertex lerp(Vertex v0, Vertex v1, float t) {
    return Vertex(Maths::lerp(v0.position, v1.position, t),
                  Maths::lerp(v0.texCoord, v1.texCoord, t),
                  Maths::lerp(v0.colour,   v1.colour,   t));
}

#endif /* Vertex_hpp  */