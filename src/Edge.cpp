// std
#include <cmath>

// my
#include "Edge.hpp"
#include "Vertex.hpp"

//------------------------------------------------------------
Edge::Edge(Vertex minY, Vertex maxY) :
    m_yStart(0)
,   m_yEnd(0)
,   m_x(0)
,   m_xStep(0.0f)
{   
    m_yStart       = static_cast<int>(std::ceil(minY.getY()));
    m_yEnd         = static_cast<int>(std::ceil(maxY.getY()));
    float xDist    = maxY.getX() - minY.getX();
    float yDist    = maxY.getY() - minY.getY();
    float yPrestep = m_yStart - minY.getY();
    m_xStep        = (float)xDist / (float)yDist;
    m_x            = minY.getX() + yPrestep * m_xStep;
}

//------------------------------------------------------------
void 
Edge::step() {
    m_x += m_xStep;
}