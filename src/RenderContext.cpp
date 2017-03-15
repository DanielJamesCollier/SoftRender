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
    std::cout << "RenderContext ctor" << std::endl;  
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

    scanTriangle(minYVert, midYVert, maxYVert, handedness);
}

//------------------------------------------------------------
void
RenderContext::scanTriangle(Vertex minY, Vertex midY, Vertex maxY, bool handedness) {
    Edge minToMax(minY, maxY);
    Edge minToMid(minY, midY);
    Edge midToMax(midY, maxY);

    // calculate the area of the outer triangle using Heron's formula
    //----------------------------------------------------------------------------
    // vec2 - E1
    float xDist_E1   = maxY.getX() - midY.getX();
    float yDist_E1   = maxY.getY() - midY.getY();
    float length_E1  = std::sqrt(xDist_E1 * xDist_E1 + yDist_E1 * yDist_E1);

    // vec2 - E2
    float xDist_E2   = maxY.getX() - minY.getX();
    float yDist_E2   = maxY.getY() - minY.getY();
    float length_E2  = std::sqrt(xDist_E2 * xDist_E2 + yDist_E2 * yDist_E2);

    // vec2 - E3
    float xDist_E3   = midY.getX() - minY.getX();
    float yDist_E3   = midY.getY() - minY.getY();
    float length_E3  = std::sqrt(xDist_E3 * xDist_E3 + yDist_E3 * yDist_E3);

    // total area of outer triangle
    float total_s    = (length_E3 + length_E2 + length_E1) * 0.5f;
    float total_area = std::sqrt(total_s * (total_s - length_E3) * (total_s - length_E2) * (total_s - length_E1));
    //----------------------------------------------------------------------------

    if(!handedness) { // left hand side vertex is lower

        for(int y = minToMid.m_yStart; y < minToMid.m_yEnd; y++) {

            // y attribute of vec2's below, only want to calculate y for every y++ not every x++
            float yDist_I1 = midY.getY() - y;
            float yDist_I2 = maxY.getY() - y;
            float yDist_I3 = y - minY.getY();

            for(int x = static_cast<int>(std::ceil(minToMax.m_x)); x < static_cast<int>(std::ceil(minToMid.m_x)); x++) {
                // get the edge vectors and their lengths
                //----------------------------------------------------------------------------
                // vec2 - I1
                float xDist_I1     = midY.getX() - x;
                float length_I1    = std::sqrt(xDist_I1 * xDist_I1 + yDist_I1 * yDist_I1);

                // vec2 - I2
                float xDist_I2     = maxY.getX() - x;
                float length_I2    = std::sqrt(xDist_I2 * xDist_I2 + yDist_I2 * yDist_I2);

                // vec2 - I3
                float xDist_I3     = x - minY.getX();
                float length_I3    = std::sqrt(xDist_I3 * xDist_I3 + yDist_I3 * yDist_I3);

                //----------------------------------------------------------------------------

                // calculate area of the 3 inner triangles using Heron's formula
                //----------------------------------------------------------------------------
                // T1 area
                float T1_s         = (length_I1 + length_I2 + length_E1) * 0.5f;
                float T1_area      = std::sqrt(T1_s * (T1_s - length_I1) * (T1_s - length_I2) * (T1_s - length_E1));
                
                // T2 area
                float T2_s         = (length_I2 + length_I3 + length_E2) * 0.5f;
                float T2_area      = std::sqrt(T2_s * (T2_s - length_I2) * (T2_s - length_I3) * (T2_s - length_E2));

                // T3 area
                float T3_s         = (length_I3 + length_I1 + length_E3) * 0.5f;
                float T3_area      = std::sqrt(T3_s * (T3_s - length_I3) * (T3_s - length_I1) * (T3_s - length_E3));
                //----------------------------------------------------------------------------

                // calculate RGB percentages and set the pixel colour
                //----------------------------------------------------------------------------
                float percentMin = T1_area / total_area;
                float percentMid = T2_area / total_area;
                float percentMax = T3_area / total_area;

                Colour x1 = percentMin * minY.colour;
                Colour x2 = percentMid * midY.colour;
                Colour x3 = percentMax * maxY.colour;

                Colour result = x1 + x2 + x3;

                setPixel(x, y, result);
                //----------------------------------------------------------------------------
            }
            minToMax.step();
            minToMid.step();
        }

        // draw the bottom half of the triangle
        for(int y = midToMax.m_yStart; y < midToMax.m_yEnd; y++) {

            float yDist_I1 = midY.getY() - y;
            float yDist_I2 = maxY.getY() - y;
            float yDist_I3 = y - minY.getY();

            for(int x = static_cast<int>(std::ceil(minToMax.m_x)); x < static_cast<int>(std::ceil(midToMax.m_x)); x++) {
                // get the edge vectors and their lengths
                //----------------------------------------------------------------------------
                // vec2 - I1
                float xDist_I1     = midY.getX() - x;
                float length_I1    = std::sqrt(xDist_I1 * xDist_I1 + yDist_I1 * yDist_I1);

                // vec2 - I2
                float xDist_I2     = maxY.getX() - x;
                float length_I2    = std::sqrt(xDist_I2 * xDist_I2 + yDist_I2 * yDist_I2);

                // vec2 - I3
                float xDist_I3     = x - minY.getX();
                float length_I3    = std::sqrt(xDist_I3 * xDist_I3 + yDist_I3 * yDist_I3);

                //----------------------------------------------------------------------------

                // get the areas of all 4 triangles
                //----------------------------------------------------------------------------
                // T1 area
                float T1_s         = (length_I1 + length_I2 + length_E1) * 0.5f;
                float T1_area      = std::sqrt(T1_s * (T1_s - length_I1) * (T1_s - length_I2) * (T1_s - length_E1));
                
                // T2 area
                float T2_s         = (length_I2 + length_I3 + length_E2) * 0.5f;
                float T2_area      = std::sqrt(T2_s * (T2_s - length_I2) * (T2_s - length_I3) * (T2_s - length_E2));

                // T3 area
                float T3_s         = (length_I3 + length_I1 + length_E3) * 0.5f;
                float T3_area      = std::sqrt(T3_s * (T3_s - length_I3) * (T3_s - length_I1) * (T3_s - length_E3));
                //----------------------------------------------------------------------------

                // calculate colour
                //----------------------------------------------------------------------------
                float percentMin = T1_area / total_area;
                float percentMid = T2_area / total_area;
                float percentMax = T3_area / total_area;

                Colour x1 = percentMin * minY.colour;
                Colour x2 = percentMid * midY.colour;
                Colour x3 = percentMax * maxY.colour;

                Colour result = x1 + x2 + x3;

                setPixel(x, y, result);
            }
            minToMax.step();
            midToMax.step();
        }
    } else { // righ hand side triangle vertex is lower
        // draw the top half of the triangle
        for(int y = minToMid.m_yStart; y < minToMid.m_yEnd; y++) {    
            
            float yDist_I1 = midY.getY() - y;
            float yDist_I2 = maxY.getY() - y;
            float yDist_I3 = y - minY.getY();

           for(int x = static_cast<int>(std::ceil(minToMid.m_x)); x < static_cast<int>(std::ceil(minToMax.m_x)); x++) {
            
                // get the edge vectors and their lengths
                //----------------------------------------------------------------------------
                // vec2 - I1
                float xDist_I1     = midY.getX() - x;
                float length_I1    = std::sqrt(xDist_I1 * xDist_I1 + yDist_I1 * yDist_I1);

                // vec2 - I2
                float xDist_I2     = maxY.getX() - x;
                float length_I2    = std::sqrt(xDist_I2 * xDist_I2 + yDist_I2 * yDist_I2);

                // vec2 - I3
                float xDist_I3     = x - minY.getX();
                float length_I3    = std::sqrt(xDist_I3 * xDist_I3 + yDist_I3 * yDist_I3);

                //----------------------------------------------------------------------------

                // get the areas of all 4 triangles
                //----------------------------------------------------------------------------
                // T1 area
                float T1_s         = (length_I1 + length_I2 + length_E1) * 0.5f;
                float T1_area      = std::sqrt(T1_s * (T1_s - length_I1) * (T1_s - length_I2) * (T1_s - length_E1));
                
                // T2 area
                float T2_s         = (length_I2 + length_I3 + length_E2) * 0.5f;
                float T2_area      = std::sqrt(T2_s * (T2_s - length_I2) * (T2_s - length_I3) * (T2_s - length_E2));

                // T3 area
                float T3_s         = (length_I3 + length_I1 + length_E3) * 0.5f;
                float T3_area      = std::sqrt(T3_s * (T3_s - length_I3) * (T3_s - length_I1) * (T3_s - length_E3));
                //----------------------------------------------------------------------------

                // calculate colour
                //----------------------------------------------------------------------------
                float percentMin = T1_area / total_area;
                float percentMid = T2_area / total_area;
                float percentMax = T3_area / total_area;

                Colour x1 = percentMin * minY.colour;
                Colour x2 = percentMid * midY.colour;
                Colour x3 = percentMax * maxY.colour;

                Colour result = x1 + x2 + x3;

                setPixel(x, y, result);
            }
            minToMid.step();
            minToMax.step();
        }

        // draw the bottom half of the triangle
        for(int y = midToMax.m_yStart; y < midToMax.m_yEnd; y++) {

            float yDist_I1 = midY.getY() - y;
            float yDist_I2 = maxY.getY() - y;
            float yDist_I3 = y - minY.getY();

            for(int x = static_cast<int>(std::ceil(midToMax.m_x)); x < static_cast<int>(std::ceil(minToMax.m_x)); x++) {
                // get the edge vectors and their lengths
                //----------------------------------------------------------------------------
                // vec2 - I1
                float xDist_I1     = midY.getX() - x;
                float length_I1    = std::sqrt(xDist_I1 * xDist_I1 + yDist_I1 * yDist_I1);

                // vec2 - I2
                float xDist_I2     = maxY.getX() - x;
                float length_I2    = std::sqrt(xDist_I2 * xDist_I2 + yDist_I2 * yDist_I2);

                // vec2 - I3
                float xDist_I3     = x - minY.getX();
                float length_I3    = std::sqrt(xDist_I3 * xDist_I3 + yDist_I3 * yDist_I3);

                //----------------------------------------------------------------------------

                // get the areas of all 4 triangles
                //----------------------------------------------------------------------------
                // T1 area
                float T1_s         = (length_I1 + length_I2 + length_E1) * 0.5f;
                float T1_area      = std::sqrt(T1_s * (T1_s - length_I1) * (T1_s - length_I2) * (T1_s - length_E1));
                
                // T2 area
                float T2_s         = (length_I2 + length_I3 + length_E2) * 0.5f;
                float T2_area      = std::sqrt(T2_s * (T2_s - length_I2) * (T2_s - length_I3) * (T2_s - length_E2));

                // T3 area
                float T3_s         = (length_I3 + length_I1 + length_E3) * 0.5f;
                float T3_area      = std::sqrt(T3_s * (T3_s - length_I3) * (T3_s - length_I1) * (T3_s - length_E3));
                //----------------------------------------------------------------------------

                // calculate colour
                //----------------------------------------------------------------------------
                float percentMin = T1_area / total_area;
                float percentMid = T2_area / total_area;
                float percentMax = T3_area / total_area;

                Colour x1 = percentMin * minY.colour;
                Colour x2 = percentMid * midY.colour;
                Colour x3 = percentMax * maxY.colour;

                Colour result = x1 + x2 + x3;

                setPixel(x, y, result);
            }
            midToMax.step();
            minToMax.step();
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
        float currYNormal = (currY - startY) / (endY - startY);

        Colour currentColour = Maths::lerp(v1.colour, v2.colour, currXNormal);
        //..

        setPixel(static_cast<int>(std::ceil(currX)), static_cast<int>(std::ceil(currY)), currentColour);
        currX += xStep;
        currY += yStep;
    }
}
