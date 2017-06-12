#ifndef Vertex_hpp
#define Vertex_hpp

// my
#include "djc_math/Vec2.hpp"
#include "djc_math/Vec3.hpp"
#include "djc_math/Mat4.hpp"
#include "djc_math/Utils.hpp"

class Mat4f;

class Vertex final {
    friend class RenderContext;
public:
    explicit Vertex(djc_math::Vec3f _position = djc_math::Vec3f(0.0f), djc_math::Vec2f _texCoord = djc_math::Vec2f(0.0f), djc_math::Vec3f _colour = djc_math::Vec3f(1.0f));
    Vertex(djc_math::Vec4f const & _position, djc_math::Vec2f _texCoord, djc_math::Vec3f _colour);
    Vertex transform(djc_math::Mat4f & matrix);
    ~Vertex() = default;

    // fix : remove these garbage functions
    float getX() const {
        return position.x;
    }

    float getY() const {
        return position.y;
    }
   
    djc_math::Vec4f position;
    djc_math::Vec2f texCoord;
    djc_math::Vec3f colour;
};

inline Vertex lerp(Vertex v0, Vertex v1, float t) {
    return Vertex(djc_math::lerp(v0.position, v1.position, t),
                  djc_math::lerp(v0.texCoord, v1.texCoord, t),
                  djc_math::lerp(v0.colour,   v1.colour,   t));
}

#endif /* Vertex_hpp  */