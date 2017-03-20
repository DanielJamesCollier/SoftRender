// my
#include "RenderContext.hpp"
#include "Colour.hpp"
#include "Edge.hpp"
#include "Maths/Maths.hpp"

// std
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <limits>

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

    // change vectors from -1 ~ 1 space to 0 ~ screenWidth
    Maths::transform(v1.position, m_screenSpaceTransform);
    Maths::transform(v2.position, m_screenSpaceTransform);
    Maths::transform(v3.position, m_screenSpaceTransform);

    Maths::perspectiveDivide(v1.position);
    Maths::perspectiveDivide(v2.position);
    Maths::perspectiveDivide(v3.position); // perf : could be inlined.

    // sort by y order
    // v1 will be minY
    // v2 will be midY
    // v3 will be maxY

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

    scanTriangle(v1, v2, v3, isleftHanded, bitmap); // perf ? chamge to if 
}

//------------------------------------------------------------
void
RenderContext::scanTriangle(Vertex const & minY, Vertex const & midY, Vertex const & maxY, bool isleftHanded, Bitmap & bitmap) {
    Edge minToMax(minY, maxY);
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
    int xMin = static_cast<int>(std::ceil(left.getX()));
    int xMax = static_cast<int>(std::ceil(right.getX()));
    float xDist = xMax - xMin;

    // starting colour - ending colour - current interpolated colour
    Maths::Vec3 minColour   = left.getColour();
    Maths::Vec3 maxColour   = right.getColour();
    Maths::Vec3 colourStep((maxColour.x - minColour.x) / xDist,
                           (maxColour.y - minColour.y) / xDist,
                           (maxColour.z - minColour.z) / xDist);
    Maths::Vec3 currColour = minColour;

    // start texCoord - ending t exCoord - current interpolated texCoord
    Maths::Vec2 minTexCoord  = left.getTexCoord();
    Maths::Vec2 maxTexCoord  = right.getTexCoord();
    Maths::Vec2 texCoordStep((maxTexCoord.x - minTexCoord.x) / xDist,
                             (maxTexCoord.y - minTexCoord.y) / xDist);
    Maths::Vec2 currTexCoord = minTexCoord;
    Maths::Vec3 texColour;

    // w
    float minW  = left.getOneOverW();
    float maxW  = right.getOneOverW();
    float wStep = (maxW - minW) / xDist;
    float currW = minW;
   

    // final output colour
    Maths::Vec3 finalColour;

    // perf : dont do perspective correction every pixel but every few pixels
    for(int x = xMin; x < xMax; x++) {

        float z = 1.0f / currW;
        
        // get the texutre colour
        texColour = bitmap.getPixel((currTexCoord.x * z) * bitmap.getWidth(),
                                    (currTexCoord.y * z) * bitmap.getHeight());

        Maths::Vec3 lerpColour = Maths::Vec3(currColour.x * z, currColour.y * z, currColour.z * z);                                    
       

        finalColour = lerpColour * texColour; // texture + colou
        //finalColour = texColour;            // texture only drawing
        //finalColour = lerpColour;           // colour only drawing

        float r = static_cast<unsigned char>(finalColour.x * 255.99f);
        float g = static_cast<unsigned char>(finalColour.y * 255.99f);
        float b = static_cast<unsigned char>(finalColour.z * 255.99f);

        if(m_depthBuffer[m_width * y + x] < currW) {
            setPixel(x, y, b, g, r);
            m_depthBuffer[m_width * y + x] = currW;
        }
        

        // step all the things
        currColour   += colourStep;
        currTexCoord += texCoordStep;
        currW        += wStep;
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

    std::fill(std::begin(m_depthBuffer), std::end(m_depthBuffer), -1000); // fix : remove this magic number
}