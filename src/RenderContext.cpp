// my
#include "RenderContext.hpp"
#include "Colour.hpp"
#include "Maths/Transform.hpp"
#include "Edge.hpp"

// std
#include <iostream>
#include <utility>
#include <cmath>

#include "Maths/Maths.hpp"

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

    if(maxYVert.getY() < midYVert.getY()) {
        std::swap(maxYVert, midYVert);
    }

    if(midYVert.getY() < minYVert.getY()) {
        std::swap(midYVert, minYVert);
    }

    if(maxYVert.getY() < midYVert.getY()) {
        std::swap(maxYVert, midYVert);
    }

    // area is neg if min is on left - positive if min is on right
    float area = minYVert.triangleAreaTimesTwo(maxYVert, midYVert);
    bool handedness = area >= 0.0f ? true : false;

    //std::cout << "handedness: " << handedness << "\narea: " << area << std::endl;
     
    // scanConvertTriangle(minYVert, midYVert, maxYVert, handedness);
    // fillShape(static_cast<int>(minYVert.getY()), static_cast<int>(maxYVert.getY())); // fix : this could be out of the window size

    scanTriangle(minYVert, midYVert, maxYVert, handedness);

}

//------------------------------------------------------------
void
RenderContext::scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool handedness) {
    Edge minToMax(minY, maxY);
    Edge minToMid(minY, midY);
    Edge midToMax(midY, maxY);

    Colour colour(1,0, 1);

    if(!handedness) {
        for(int y = minToMid.m_yStart; y < minToMid.m_yEnd; y++) {
            for(int x = minToMax.m_x; x < minToMid.m_x; x++) {
                setPixel(x, y, colour);
            }
            minToMax.step();
            minToMid.step();
        }

        // draw the bottom half of the triangle
        for(int y = midToMax.m_yStart; y < midToMax.m_yEnd; y++) {
            for(int x = minToMax.m_x; x < midToMax.m_x; x++) {
                setPixel(x, y, colour);
            }
            minToMax.step();
            midToMax.step();
        }
    } else {
            // draw the top half of the triangle
        for(int y = minToMid.m_yStart; y < minToMid.m_yEnd; y++) {    
           for(int x = minToMid.m_x; x < minToMax.m_x; x++) {
                    setPixel(x, y, colour);
            }
            minToMax.step();
            minToMid.step();
        }

        // draw the bottom half of the triangle
        for(int y = midToMax.m_yStart; y < midToMax.m_yEnd; y++) {
            for(int x = midToMax.m_x; x < minToMax.m_x; x++) {
                setPixel(x, y, colour);
            }
            minToMax.step();
            midToMax.step();
        }
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
    std::cout <<"v1 colour: " << v1.colour << std::endl;
    std::cout << "v2 colour: " << v2.colour << std::endl;
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

        // current x and y normaised
        float currXNormal = (currX - startX) / (endX - startX);
        float currYNormal = (currY - startY) / (endY - startY);

        Colour currentColour = Maths::lerp(v1.colour, v2.colour, currXNormal);
       

        //..
        setPixel(static_cast<int>(std::ceil(currX)), static_cast<int>(std::ceil(currY)), currentColour);
        currX += xStep;
        currY += yStep;
    }
}

// colour interpolation

// lerp t = currX
// curr x must be between 0 & 1
// lep v1 a v2 are colours


// how to get current x between 0 & 1

// startX & endX

// min = 245
// max = -100

// item to norm = 56
