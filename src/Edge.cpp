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
{   
    float xDist = maxY.getX() - minY.getX();
    float yDist = maxY.getY() - minY.getY();
    // float yPrestep = m_yStart - minY.getY();

    m_xStep  = xDist / yDist;
    // m_x            = minY.getX() + yPrestep * m_xStep;

    float minOneOverW = 1.0f / minY.position.w;
    float maxOneOverW = 1.0f / maxY.position.w;

    m_oneOverW = minOneOverW;
    m_oneOverW_step = (maxOneOverW - minOneOverW) / yDist;

    
    Maths::Vec2 texMinCorrected = minY.texCoord / minY.position.w;
    Maths::Vec2 texMaxCorrected = maxY.texCoord / maxY.position.w;
    m_texCoord = texMinCorrected;
    m_texCoordStep = Maths::Vec2((texMaxCorrected.x - texMinCorrected.x) / yDist,
                                 (texMaxCorrected.y - texMinCorrected.y) / yDist);
                                 


    // calc how much to increment colour per step
    Maths::Vec3 colMinCorrected = minY.colour / minY.position.w;
    Maths::Vec3 colMaxCorrected = maxY.colour / maxY.position.w;

    m_colour = colMinCorrected;

    m_colourStep = Maths::Vec3((colMaxCorrected.x - colMinCorrected.x) / yDist,
                               (colMaxCorrected.y - colMinCorrected.y) / yDist,
                               (colMaxCorrected.z - colMinCorrected.z) / yDist);
}

//------------------------------------------------------------
void 
Edge::step() {
    m_x           += m_xStep;
    m_oneOverW    += m_oneOverW_step;
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
Edge::getOneOverW() const {
    return m_oneOverW;
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