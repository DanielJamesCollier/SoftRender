// my
#include "RenderContext.hpp"
#include "Colour.hpp"
#include "Maths/Transform.hpp"
#include "Edge.hpp"
#include "Maths/Maths.hpp"

// std
#include <iostream>
#include <utility>
#include <cmath>

//------------------------------------------------------------
RenderContext::RenderContext(int width, int height) :
    Bitmap(width, height)
{
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    std::cout << "context width: " << width << " context height: " << height << std::endl;  
}

//------------------------------------------------------------
void // fix : call this function when screen size changes - need to account for scale
RenderContext::updateContextSize(float width, float height) {
    m_width = width;
    m_height = height;
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    m_buffer.resize(m_width * m_height * 4);
}

//------------------------------------------------------------
void
RenderContext::fillTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap) {
    Vertex minYVert = v1;
    Vertex midYVert = v2;
    Vertex maxYVert = v3;

    minYVert = minYVert.transform(m_screenSpaceTransform).perspectiveDivide();
    midYVert = midYVert.transform(m_screenSpaceTransform).perspectiveDivide();
    maxYVert = maxYVert.transform(m_screenSpaceTransform).perspectiveDivide();

    if(maxYVert.getY() < midYVert.getY()) {
        std::swap(maxYVert, midYVert);
    }

    if(midYVert.getY() < minYVert.getY()) {
        std::swap(midYVert, minYVert);
    }

    if(maxYVert.getY() < midYVert.getY()) {
        std::swap(maxYVert, midYVert);
    }

    // area is neg if mid is on left - positive if mid is on right
    float area = minYVert.triangleAreaTimesTwo(maxYVert, midYVert);
    bool handedness = area >= 0.0f ? true : false; // true is mid on right

    scanTriangle(minYVert, midYVert, maxYVert, handedness, bitmap);
}

//------------------------------------------------------------
void
RenderContext::scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool handedness, Bitmap & bitmap) {
    Edge minToMax(minY, maxY);
    Edge minToMid(minY, midY);
    Edge midToMax(midY, maxY);

    if(!handedness) { // midX < minX

        // top portion
        for(int y = minToMid.getYStart(); y < minToMid.getYEnd(); y++) {
            drawScanLine(minToMax, minToMid, y);
            minToMid.step();
            minToMax.step();
        }

        // bottom portion
        for(int y = midToMax.getYStart(); y < midToMax.getYEnd(); y++) {
            drawScanLine(minToMax, midToMax, y);
            minToMax.step();
            midToMax.step();
        }

    }
    else // midX > minX
    {
        for(int y = minToMid.getYStart(); y < minToMid.getYEnd(); y++) {
            drawScanLine(minToMid, minToMax, y);
            minToMax.step();
            minToMid.step();
        }

        // bottom portion
        for(int y = midToMax.getYStart(); y < midToMax.getYEnd(); y++) {
            drawScanLine(midToMax, minToMax, y);
            minToMax.step();
            midToMax.step();
        }
    }
}

//------------------------------------------------------------
void 
RenderContext::drawScanLine(Edge left, Edge right, int y) {
    int xMin = static_cast<int>(std::ceil(left.getX()));
    int xMax = static_cast<int>(std::ceil(right.getX()));

    for(int x = xMin; x < xMax; x++) {
        setPixel(x, y, Colour(0,0,1));
    }
}

//------------------------------------------------------------
void
RenderContext::wireTriangle(Vertex v1, Vertex v2, Vertex v3) {
    drawLine(v1, v2);
    drawLine(v2, v3);
    drawLine(v3, v1);
}

//------------------------------------------------------------
void
RenderContext::drawLine(Vertex v1, Vertex v2) {
    // transform input vector4 into screen space from -1 to 1
    //  do perspective perspectiveDivide
    v1 = v1.transform(m_screenSpaceTransform).perspectiveDivide();
    v2 = v2.transform(m_screenSpaceTransform).perspectiveDivide();

    // vec2 
    float startY = v1.position.y;
    float startX = v1.position.x;

    // vec 2 
    float endX = v2.position.x;
    float endY = v2.position.y;

    // vec 2 
    float xDist = endX - startX;
    float yDist = endY - startY;

    // length of above
    float length = std::sqrt(xDist * xDist + yDist * yDist);

    // how many pixels to move in x an y axis per for loop itter
    float xStep = xDist / length;
    float yStep = yDist / length;

    // startiny x and y - will be incremented
    float currX = startX;
    float currY = startY;

    // draw all the pixels ever
    for(int i = 0; i < static_cast<int>(length); i++) {

        // get the interpolated colour
        float currXNormal = (currX - startX) / (endX - startX);
        //float currYNormal = (currY - startY) / (endY - startY);

        Colour currentColour = Maths::lerp(v1.colour, v2.colour, currXNormal);
        //..

        setPixel(static_cast<int>(std::ceil(currX)), static_cast<int>(std::ceil(currY)), currentColour);
        currX += xStep;
        currY += yStep;
    }
}