#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4.hpp"
#include "Maths/Utils.hpp"

class Mat4f;

class Vertex {
    friend class RenderContext;
public:
    Vertex(djc_math::Vec3<float> _position, djc_math::Vec2<float> _texCoord = djc_math::Vec2<float>(0,0), djc_math::Vec3<float> _colour = djc_math::Vec3<float>(1, 1, 1));
    Vertex(djc_math::Vec4<float> const & _position, djc_math::Vec2<float> _texCoord, djc_math::Vec3<float> _colour);

    Vertex transform(djc_math::Mat4<float> & matrix);

    // fix : remove these garbage functions
    float getX() const {
        return position.x;
    }

    float getY() const {
        return position.y;
    }
   
    djc_math::Vec4<float> position;
    djc_math::Vec2<float> texCoord;
    djc_math::Vec3<float> colour;
};

inline Vertex lerp(Vertex v0, Vertex v1, float t) {
    return Vertex(djc_math::lerp(v0.position, v1.position, t),
                  djc_math::lerp(v0.texCoord, v1.texCoord, t),
                  djc_math::lerp(v0.colour,   v1.colour,   t));
}

#endif /* Vertex_hpp  */