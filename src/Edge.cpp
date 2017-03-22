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
,   x(minY.getX())
{   
    float yDist = maxY.position.y - minY.position.y;

    m_xStep  = (maxY.position.x - minY.position.x) / yDist;


    oneOverW = 1.0f / minY.position.w;;
    m_oneOverW_step = ((1.0f / maxY.position.w) - oneOverW) / yDist;

    
   
    texCoord = minY.texCoord / minY.position.w;
    Maths::Vec2 texMaxCorrected = maxY.texCoord / maxY.position.w;
    m_texCoordStep = Maths::Vec2((texMaxCorrected.x - texCoord.x) / yDist,
                                 (texMaxCorrected.y - texCoord.y) / yDist);
                                 


    // calc how much to increment colour per step
    colour = minY.colour / minY.position.w;
    Maths::Vec3 colMaxCorrected = maxY.colour / maxY.position.w;

    m_colourStep = Maths::Vec3((colMaxCorrected.x - colour.x) / yDist,
                               (colMaxCorrected.y - colour.y) / yDist,
                               (colMaxCorrected.z - colour.z) / yDist);
}

//------------------------------------------------------------
void 
Edge::step() {
    x        += m_xStep;
    oneOverW += m_oneOverW_step;
    colour   += m_colourStep;
    texCoord += m_texCoordStep;
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