// std
#include <cmath>

// my
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Maths/MathsUtils.hpp"

//------------------------------------------------------------
Edge::Edge(Vertex const & minY, Vertex const & maxY) :
    m_yStart(static_cast<int>(std::ceil(minY.getY())))
,   m_yEnd(static_cast<int>(std::ceil(maxY.getY())))
,   m_x(minY.getX())
,   m_w(minY.position.w)
,   m_colour(minY.colour)
,   m_texCoord(minY.texCoord)
{   
    float xDist = maxY.getX() - minY.getX();
    float yDist = maxY.getY() - minY.getY();
   // float yPrestep = m_yStart - minY.getY();

    m_xStep  = xDist / yDist;
   // m_x            = minY.getX() + yPrestep * m_xStep;

    // calc how much to increment tex per step
    m_texCoordStep = Maths::Vec2((maxY.texCoord.x - minY.texCoord.x) / yDist,
                                 (maxY.texCoord.y - minY.texCoord.y) / yDist);

    // calc how much to increment w per step
    m_wStep = (maxY.position.w - minY.position.w) / yDist;

    // calc how much to increment colour per step
    m_colourStep = Maths::Vec3((maxY.colour.x - minY.colour.x) / yDist,
                               (maxY.colour.y - minY.colour.y) / yDist,
                               (maxY.colour.z - minY.colour.z) / yDist);
}

//------------------------------------------------------------
void 
Edge::step() {
    m_x           += m_xStep;
    m_w           += m_wStep;
    m_colour      += m_colourStep;
    m_texCoord    += m_texCoordStep;
}

//------------------------------------------------------------
float 
Edge::getYStart() const {
    return m_yStart;
}

//------------------------------------------------------------
float 
Edge::getYEnd() const {
    return m_yEnd;
}

//------------------------------------------------------------
float 
Edge::getX() const {
    return m_x;
}

//------------------------------------------------------------
float 
Edge::getW() const {
    return m_w;
}

//------------------------------------------------------------
Maths::Vec3 const &
Edge::getColour() const {
    return m_colour;
}

//------------------------------------------------------------
Maths::Vec2 const & 
Edge::getTexCoord() const {
    return m_texCoord;
}