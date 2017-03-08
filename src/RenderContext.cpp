// my
#include "RenderContext.hpp"
#include "Colour.hpp"
#include "Maths/Transform.hpp"
#include "Edge.hpp"

// std
#include <iostream>
#include <utility>
#include <cmath>

//------------------------------------------------------------
RenderContext::RenderContext(int width, int height) :
    Bitmap(width, height)
{
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    std::cout << "RenderContext ctor" << std::endl;  
}

//------------------------------------------------------------
void // fix : call this function when screen size changes
RenderContext::updateContextSize(float width, float height) {
    m_width = width;
    m_height = height;
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    m_buffer.resize(m_width * m_height * 4);
}

//------------------------------------------------------------
void
RenderContext::fillTriangle(Vertex v1, Vertex v2, Vertex v3) {
    
    Vertex minYVert = v1;
    Vertex midYVert = v2;
    Vertex maxYVert = v3;

    minYVert = minYVert.transform(m_screenSpaceTransform).perspectiveDivide();
    midYVert = midYVert.transform(m_screenSpaceTransform).perspectiveDivide();
    maxYVert = maxYVert.transform(m_screenSpaceTransform).perspectiveDivide();

    if(maxYVert.getY() < midYVert.getY())
    {
        Vertex temp = maxYVert;
        maxYVert = midYVert;
        midYVert = temp;
    }

    if(midYVert.getY() < minYVert.getY())
    {
        Vertex temp = midYVert;
        midYVert = minYVert;
        minYVert = temp;
    }

    if(maxYVert.getY() < midYVert.getY())
    {
        Vertex temp = maxYVert;
        maxYVert = midYVert;
        midYVert = temp;
    }

    // area is neg if min is on left - positive if min is on right
    float area = minYVert.triangleAreaTimesTwo(maxYVert, midYVert);
    int handedness = area >= 0 ? 1 : 0;

    //std::cout << "handedness: " << handedness << "\narea: " << area << std::endl;
     
    // scanConvertTriangle(minYVert, midYVert, maxYVert, handedness);
    // fillShape(static_cast<int>(minYVert.getY()), static_cast<int>(maxYVert.getY())); // fix : this could be out of the window size

    scanTriangle(minYVert, midYVert, maxYVert, handedness);

}

//------------------------------------------------------------
void
RenderContext::scanTriangle(Vertex minY, Vertex midY, Vertex maxY, int handedness) {
    Edge minToMax(minY, maxY);
    Edge minToMid(minY, midY);
    Edge midToMax(midY, maxY);

    Colour colour(0,0, 200);

    // draw the top half of the triangle
    for(int y = minToMid.m_yStart; y < minToMid.m_yEnd; y++) {
        if(handedness == 0) {
            for(int x = minToMax.m_x; x < minToMid.m_x; x++) {
                setPixel(x, y, colour);
            }
        } else { // handedness == 1
            for(int x = minToMid.m_x; x < minToMax.m_x; x++) {
                setPixel(x, y, colour);
            }
        }
        
        minToMax.step();
        minToMid.step();
    }

    // draw the bottom half of the triangle
    for(int y = midToMax.m_yStart; y < midToMax.m_yEnd; y++) {
        if(handedness == 0) {
            for(int x = minToMax.m_x; x < midToMax.m_x; x++) {
                setPixel(x, y, colour);
            }
        } else { // handedness == 1
            for(int x = midToMax.m_x; x < minToMax.m_x; x++) {
                setPixel(x, y, colour);
            }
        }
    
        minToMax.step();
        midToMax.step();
    }
}