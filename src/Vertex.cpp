// my
#include "Vertex.hpp"

//------------------------------------------------------------
Vertex::Vertex(Maths::Vec3 _position, Maths::Vec2 _texCoord, Colour _colour) :   
    position(_position, 1.0f)
,   texCoord(_texCoord)
,   colour(_colour)
{
    // empty
}

//------------------------------------------------------------
Vertex::Vertex(Maths::Vec4 const & _position, Maths::Vec2 _texCoord, Colour _colour) :   
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

//------------------------------------------------------------
Vertex
Vertex::perspectiveDivide() {
    return Vertex(Maths::Vec4(position.x / position.w,
                  position.y / position.w,
                  position.z / position.w,
                  position.w), texCoord, colour);
}

//------------------------------------------------------------
float
Vertex::triangleAreaTimesTwo(Vertex const & b, Vertex const & c) {
    float x1 = b.position.x - position.x;
    float y1 = b.position.y - position.y;

    float x2 = c.position.x - position.x;
    float y2 = c.position.y - position.y;

    return x1 * y2 - x2 * y1;
}


