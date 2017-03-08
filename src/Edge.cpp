// std
#include <cmath>

// my
#include "Edge.hpp"
#include "Vertex.hpp"

//------------------------------------------------------------
Edge::Edge(Vertex minY, Vertex maxY) {
    m_yStart   = (int)minY.getY();
    m_yEnd     = (int)maxY.getY();
    int xStart = (int)minY.getX();
    int xEnd   = (int)maxY.getX();
    int xDist  = xEnd - xStart;
    int yDist  = m_yEnd - m_yStart;

    m_xStep = float(xDist) / float(yDist);
    m_x     = float(xStart);
}

//------------------------------------------------------------
void 
Edge::step() {
    m_x += m_xStep;
}
