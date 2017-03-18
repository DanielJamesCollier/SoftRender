// my
#include "Vertex.hpp"

//------------------------------------------------------------
Vertex::Vertex(Maths::Vec3 _position, Maths::Vec2 _texCoord, Maths::Vec3 _colour) :   
    position(_position, 1.0f)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex::Vertex(Maths::Vec4 const & _position, Maths::Vec2 _texCoord, Maths::Vec3 _colour) :   
    position(_position)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex 
Vertex::transform(Maths::Mat4f & matrix) { 
    Maths::Vec4 pos = matrix * position;
    return Vertex(Maths::Vec4(pos.x, pos.y, pos.z, pos.w), texCoord, colour); 
}

