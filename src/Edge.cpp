// std
#include <cmath>

// my
#include "Edge.hpp"
#include "Vertex.hpp"

//------------------------------------------------------------
Edge::Edge(Vertex minY, Vertex maxY) {
    m_yStart   = static_cast<int>(std::ceil(minY.getY()));
    m_yEnd     = static_cast<int>(std::ceil(maxY.getY()));
    int xStart = static_cast<int>(std::ceil(minY.getX()));
    int xEnd   = static_cast<int>(std::ceil(maxY.getX()));
    
    float xDist  = maxY.getX() - minY.getX();
    float yDist  = maxY.getY() - minY.getY();

    m_xStep = xDist / yDist;
    float yPrestep = m_yStart - minY.getY();
    m_x = minY.getX() + yPrestep * m_xStep;
}

//------------------------------------------------------------
void 
Edge::step() {
    m_x += m_xStep;
}
