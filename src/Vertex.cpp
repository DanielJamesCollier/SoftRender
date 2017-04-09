// my
#include "Vertex.hpp"

//------------------------------------------------------------
Vertex::Vertex(djc_math::Vec3f _position, djc_math::Vec2f _texCoord, djc_math::Vec3f _colour) :   
    position(_position, 1.0f)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex::Vertex(djc_math::Vec4f const & _position, djc_math::Vec2f _texCoord, djc_math::Vec3f _colour) :   
    position(_position)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex 
Vertex::transform(djc_math::Mat4f & matrix) { 
    auto pos = matrix * position;
    return Vertex(djc_math::Vec4f(pos.x, pos.y, pos.z, pos.w), texCoord, colour); 
}

