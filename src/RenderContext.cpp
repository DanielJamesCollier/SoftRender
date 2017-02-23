// my
#include "RenderContext.hpp"
#include "Colour.hpp"
// std
#include <iostream>

//---------------------------------------------------------
RenderContext::RenderContext(int width, int height) :
    Bitmap(width, height)
{
    m_scanBuffer.resize(height * 2);
}

//---------------------------------------------------------
void
RenderContext::drawScanBuffer(int y, int xMin, int xMax) {
    m_scanBuffer[y * 2 + 0] = xMin;
    m_scanBuffer[y * 2 + 1] = xMax;
}

//---------------------------------------------------------
void
RenderContext::fillShape(int yMin, int yMax) {
    for(int j = yMin; j < yMax; j++) {
        int xMin = m_scanBuffer[j * 2 + 0];
        int xMax = m_scanBuffer[j * 2 + 1];
            
        for(int i = xMin; i < xMax; i++) {
            setPixel(i, j, Colour(255, 0, 0));
        }
    }
}

//---------------------------------------------------------
void
RenderContext::scanConvertTriangle(Maths::Vec3 const & minY,
                                   Maths::Vec3 const & midY,
                                   Maths::Vec3 const & maxY,
                                   int handedness) {
    scanConvertLine(minY, maxY, 0 + handedness);
    scanConvertLine(minY, midY, 1 - handedness);
    scanConvertLine(midY, maxY, 1 - handedness);
}

//---------------------------------------------------------
void
RenderContext::scanConvertLine(Maths::Vec3 const & minY, Maths::Vec3 const & maxY, int handedness) {
    int yBegin = static_cast<int>(minY.getY());
    int yEnd = static_cast<int>(maxY.getY());
    int yDistance = yEnd - yBegin;

    if(yDistance <= 0) return;

    int xBegin = static_cast<int>(minY.getX());
    int xEnd = static_cast<int>(maxY.getX());
    int xDistance = xEnd - xBegin;

    float stepX = static_cast<float>(xDistance) / static_cast<float>(yDistance); 
    float currentX = xBegin;

    for (int y = yBegin; y < yEnd; y++) {
        m_scanBuffer[y * 2 + handedness] = static_cast<int>(currentX);
        currentX += stepX;
    }
}