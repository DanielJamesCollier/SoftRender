// my
#include "RenderContext.hpp"
#include "Colour.hpp"
// std
#include <iostream>
#include <utility>

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
RenderContext::fillTriangle(Maths::Vec3 v1, Maths::Vec3 v2, Maths::Vec3 v3) {

    // v1 = minY
    // v2 = midY
    // v3 = maxY

    if(v3.getY() < v2.getY()) {
        std::swap(v3, v2);
    }

    if(v2.getY() < v1.getY()) {
        std::swap(v2, v1);
    }

    if(v3.getY() < v2.getY()) {
        std::swap(v3, v2);
    }

    auto triangleArea = [&]() -> float {
        float x1 = v3.getX() - v1.getX();
        float y1 = v3.getY() - v1.getY();
        float x2 = v2.getX() - v1.getX();
        float y2 = v2.getY() - v1.getY();

        return (x1 * y2 - x2 * y1);
    };

    float area = triangleArea();

    int handedness = area >= 0 ? 1 : 0;

    scanConvertTriangle(v1, v2, v3, handedness);
    fillShape(static_cast<int>(v1.getY()), static_cast<int>(v3.getY()));
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