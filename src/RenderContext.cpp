// my
#include "RenderContext.hpp"
#include "Colour.hpp"
#include "Maths/Transform.hpp"

// std
#include <iostream>
#include <utility>
#include <cmath>

//------------------------------------------------------------
RenderContext::RenderContext(int width, int height) :
    Bitmap(width, height)
{
    m_scanBuffer.resize(height * 2);
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    std::cout << "RenderContext ctor" << std::endl;  
}

//------------------------------------------------------------
void
RenderContext::drawScanBuffer(int y, int xMin, int xMax) {
    m_scanBuffer[y * 2 + 0] = xMin; // todo : array bounds check ?
    m_scanBuffer[y * 2 + 1] = xMax;
}

//------------------------------------------------------------
void
RenderContext::fillShape(int yMin, int yMax) {
    for(int j = yMin; j < yMax; j++) {
        int xMin = m_scanBuffer[j * 2 + 0]; // todo : array bounds check ??
        int xMax = m_scanBuffer[j * 2 + 1];
            
        for(int i = xMin; i < xMax; i++) {
            setPixel(i, j, Colour(255, 0, 0)); // fix : this could be out of the window size - do -1 - 1 scaling before looking athis
        }
    }
}

//------------------------------------------------------------
void // fix : call this function when screen size changes
RenderContext::updateContextSize(float width, float height) {
    m_width = width;
    m_height = height;
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    m_buffer.resize(m_width * m_height * 4);
    m_scanBuffer.resize(m_height * 2);
}

//------------------------------------------------------------
void
RenderContext::fillTriangle(Vertex v1, Vertex v2, Vertex v3) {
    // convert from (-1, 1) to (0, width) or (0, height)
    v1 = v1.transform(m_screenSpaceTransform).perspectiveDivide();
    v2 = v2.transform(m_screenSpaceTransform).perspectiveDivide();
    v3 = v3.transform(m_screenSpaceTransform).perspectiveDivide();

    // sort the input vertices into the following
    // v1 = minY
    // v2 = midY
    // v3 = maxY

    if(v3.position.y < v2.position.y) {
        std::swap(v3, v2);
    }

    if(v2.position.y < v1.position.y) {
        std::swap(v2, v1);
    }

    if(v3.position.y < v2.position.y) {
        std::swap(v3, v2);
    }

    auto triangleAreaTimesTwo = [&]() -> float {
        float x1 = v3.position.x - v1.position.x;
        float y1 = v3.position.y - v1.position.y;
        float x2 = v2.position.x - v1.position.x;
        float y2 = v2.position.y - v1.position.y;
        return (x1 * y2 - x2 * y1);
    };

    float area = triangleAreaTimesTwo();

    int handedness = area >= 0 ? 1 : 0;
    
    scanConvertTriangle(v1.position, v2.position, v3.position, handedness);
    fillShape(static_cast<int>(std::ceil(v1.position.y)), static_cast<int>(std::ceil(v3.position.y))); // fix : this could be out of the window size
}

//------------------------------------------------------------
void
RenderContext::scanConvertTriangle(Maths::Vec4 const & minY,
                                   Maths::Vec4 const & midY,
                                   Maths::Vec4 const & maxY,
                                   int handedness) {
    scanConvertLine(minY, maxY, 0 + handedness);
    scanConvertLine(minY, midY, 1 - handedness);
    scanConvertLine(midY, maxY, 1 - handedness);
}

//------------------------------------------------------------
void
RenderContext::scanConvertLine(Maths::Vec4 const & minY, Maths::Vec4 const & maxY, int handedness) {
    int yBegin      = static_cast<int>(std::ceil(minY.y));
    int yEnd        = static_cast<int>(std::ceil(maxY.y));
    float yDistance = maxY.y - minY.y;

    if(yDistance <= 0) return;

    int xBegin      = static_cast<int>(std::ceil(minY.x));
    int xEnd        = static_cast<int>(std::ceil(maxY.x));
    float xDistance = maxY.x - minY.x;

    float stepX = xDistance / yDistance; 
    float yPreset = yBegin -  minY.y;
    float currentX =  minY.x + yPreset * stepX;

    for (int y = yBegin; y < yEnd; y++) {
        m_scanBuffer[y * 2 + handedness] = static_cast<int>(std::ceil(currentX)); // todo : array bounds check ?
        currentX += stepX;
    }
}