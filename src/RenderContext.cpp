// my
#include "RenderContext.hpp"
#include "Edge.hpp"
#include "Maths/Maths.hpp"

// std
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <limits>

/* PUBLIC */

//------------------------------------------------------------
RenderContext::RenderContext(int width, int height) :
    Bitmap(width, height)
{   
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    std::cout << "context width: " << width << " context height: " << height << std::endl;  

    m_depthBuffer.resize(width * height);
    std::fill(std::begin(m_depthBuffer), std::end(m_depthBuffer), -100);
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
    v1 = v1.transform(m_screenSpaceTransform);
    v2 = v2.transform(m_screenSpaceTransform);

    Maths::perspectiveDivide(v1.position);
    Maths::perspectiveDivide(v2.position);

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

        Maths::Vec3 currentColour = Maths::lerp(v1.colour, v2.colour, currXNormal);
        //..

       // setPixel(static_cast<int>(std::ceil(currX)), static_cast<int>(std::ceil(currY)), currentColour);
        currX += xStep;
        currY += yStep;
    }
}

//------------------------------------------------------------
void
RenderContext::drawMesh(std::vector<Vertex> mesh, Maths::Mat4f & transform, Bitmap & bitmap) {  

    // transform vertices
    for(size_t i = 0; i < mesh.size(); i++) {
        Maths::transform(mesh[i].position, transform);
    }

    // draw triangles
    for(size_t i = 0; i < mesh.size(); i+= 3) {
        //std::sort(mesh);
        fillTriangle(mesh[i + 0],
                     mesh[i + 1],
                     mesh[i + 2],
                     bitmap);
    }    
}

//------------------------------------------------------------
void 
RenderContext::drawIndexedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> const & indices, Maths::Mat4f & transform, Bitmap & bitmap) {
     // transform vertices
    for(size_t i = 0; i < vertices.size(); i++) {
        Maths::transform(vertices[i].position, transform);
    }

    // draw triangles
    for(size_t i = 0; i < indices.size(); i+= 3) {
        //std::sort(mesh);
        fillTriangle(vertices[indices[i + 0]],
                     vertices[indices[i + 1]],
                     vertices[indices[i + 2]],
                     bitmap);
    }
}

//------------------------------------------------------------
void
RenderContext::clearDepthBuffer() {
    std::fill(std::begin(m_depthBuffer), std::end(m_depthBuffer), -1000); // fix : remove this magic number
}

/* PRIVATE */

//------------------------------------------------------------
void
RenderContext::fillTriangle(Vertex & v1, Vertex  & v2, Vertex & v3, Bitmap & bitmap) {

    // change vectors from -1 ~ 1 space to 0 ~ screenWidth
    Maths::transform(v1.position, m_screenSpaceTransform);
    Maths::transform(v2.position, m_screenSpaceTransform);
    Maths::transform(v3.position, m_screenSpaceTransform);

    Maths::perspectiveDivide(v1.position);
    Maths::perspectiveDivide(v2.position);
    Maths::perspectiveDivide(v3.position); // perf : could be inlined.


    if(v3.getY() < v2.getY()) {
        std::swap(v3, v2);
    }

    if(v2.getY() < v1.getY()) {
        std::swap(v2, v1);
    }

    if(v3.getY() < v2.getY()) {
        std::swap(v3, v2);
    }

    bool isleftHanded = v2.getX() >= v1.getX() ? true : false;

    scanTriangle(v1, v2, v3, isleftHanded, bitmap);
}

//------------------------------------------------------------
void
RenderContext::scanTriangle(Vertex const & minY, Vertex const & midY, Vertex const & maxY, bool isleftHanded, Bitmap & bitmap) {
    Edge minToMax(minY, maxY); // perf : alot of data gets duplicated here
    Edge minToMid(minY, midY);
    Edge midToMax(midY, maxY);

    if(isleftHanded) {
        // top 
        for(int y = minToMid.getYStart(); y < minToMid.getYEnd(); y++) {
            drawScanLine(minToMax, minToMid, y, bitmap);
            minToMax.step();
            minToMid.step();
        }

        for(int y = midToMax.getYStart(); y < midToMax.getYEnd(); y++) {
            drawScanLine(minToMax, midToMax, y, bitmap);
            minToMax.step();
            midToMax.step();
        }
    }
    else 
    {   
        // top
        for(int y = minToMid.getYStart(); y < minToMid.getYEnd(); y++) {
            drawScanLine(minToMid, minToMax,y, bitmap);
            minToMid.step();
            minToMax.step();
        }

        for(int y = midToMax.getYStart(); y < midToMax.getYEnd(); y++) {
            drawScanLine(midToMax, minToMax, y, bitmap);
            minToMax.step();
            midToMax.step();
        }
    }
}

//------------------------------------------------------------
void 
RenderContext::drawScanLine(Edge const & left, Edge const & right, int y, Bitmap & bitmap) {
    float xMin  = static_cast<int>(std::ceil(left.x));
    float xMax  = static_cast<int>(std::ceil(right.x));
    float xDist = xMax - xMin;

    Maths::Vec3 currColour = left.colour;
    Maths::Vec3 colourStep((right.colour - left.colour) / xDist);

    Maths::Vec2 currTexCoord = left.texCoord;
    Maths::Vec2 texCoordStep((right.texCoord - left.texCoord) / xDist);

    float currW = left.oneOverW;
    float wStep = (right.oneOverW - currW) / xDist;


    // perf : dont do perspective correction every pixel but every few pixels
    for(float x = xMin; x < xMax; ++x) {

        if(m_depthBuffer[m_width * y + x] > currW) return;
        m_depthBuffer[m_width * y + x] = currW;

        float z = 1.0f / currW;
        
        Maths::Vec3 correctedTexColour = bitmap.getPixel((currTexCoord.x * z) * bitmap.getWidthF(), (currTexCoord.y * z) * bitmap.getHeightF());
        Maths::Vec3 correctedColour = Maths::Vec3(currColour.x * z, currColour.y * z, currColour.z * z);                                    
    
        Maths::Vec3 finalColour = correctedColour * correctedTexColour;


        setPixel(x, y, 
                    static_cast<unsigned char>(finalColour.z * 255.99f),
                    static_cast<unsigned char>(finalColour.y * 255.99f), 
                    static_cast<unsigned char>(finalColour.x * 255.99f));
        

        // step all the things
        currColour   += colourStep;
        currTexCoord += texCoordStep;
        currW        += wStep;
    }
}

//------------------------------------------------------------
void // fix : call this function when screen size changes - need to account for scale
RenderContext::updateContextSize(float width, float height) {
    m_screenSpaceTransform = Maths::createScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    Bitmap::resize(width, height);
}