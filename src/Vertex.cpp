// my
#include "Vertex.hpp"

//------------------------------------------------------------
Vertex::Vertex(djc_math::Vec3<float> _position, djc_math::Vec2<float> _texCoord, djc_math::Vec3<float> _colour) :   
    position(_position, 1.0f)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex::Vertex(djc_math::Vec4<float> const & _position, djc_math::Vec2<float> _texCoord, djc_math::Vec3<float> _colour) :   
    position(_position)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex 
Vertex::transform(djc_math::Mat4<float> & matrix) { 
    djc_math::Vec4<float> pos = matrix * position;
    return Vertex(djc_math::Vec4<float>(pos.x, pos.y, pos.z, pos.w), texCoord, colour); 
}

