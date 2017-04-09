// my
#include "RenderContext.hpp"
#include "Edge.hpp"

#include "Maths/djc_math.hpp"

// std
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdint> // used for inline asm
#include <limits>

/* PUBLIC */

//------------------------------------------------------------
RenderContext::RenderContext(int width, int height) :
    Bitmap(width, height)
{   
    m_screenSpaceTransform = djc_math::createMat4ScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f); 

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
void // fix to use edges
RenderContext::drawLine(Vertex v1, Vertex v2) {
    v1 = v1.transform(m_screenSpaceTransform);
    v2 = v2.transform(m_screenSpaceTransform);

    djc_math::perspectiveDivide(v1.position);
    djc_math::perspectiveDivide(v2.position);

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

        auto currentColour = djc_math::lerp(v1.colour, v2.colour, currXNormal);
        //..

       // setPixel(static_cast<int>(std::ceil(currX)), static_cast<int>(std::ceil(currY)), currentColour);
        currX += xStep;
        currY += yStep;
    }
}

//------------------------------------------------------------
void
RenderContext::drawTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap) {
    // clip triangle
    std::vector<Vertex> vertices;
    std::vector<Vertex> vertricesClipped;

    vertices.reserve(3);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    if(clipPolygonAxis(vertices, vertricesClipped, 0) &&
       clipPolygonAxis(vertices, vertricesClipped, 1) &&
       clipPolygonAxis(vertices, vertricesClipped, 2)) {
           
        // triangle fan drawing
        for(int i = 1; i < vertices.size() - 1; i++) {
            fillTriangle(vertices[0], vertices[i], vertices[i + 1], bitmap);
        }
    }
}

//------------------------------------------------------------
void
RenderContext::drawMesh(std::vector<Vertex> mesh, djc_math::Mat4<float> & transform, Bitmap & bitmap) {  

    // transform vertices
    for(size_t i = 0; i < mesh.size(); i++) {
        mesh[i].position = transform * mesh[i].position;
    }

    // draw triangles
    for(size_t i = 0; i < mesh.size(); i+= 3) {
        drawTriangle(mesh[i + 0],
                     mesh[i + 1],
                     mesh[i + 2],
                     bitmap);
    }    
}

//------------------------------------------------------------
void 
RenderContext::drawIndexedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> const & indices, djc_math::Mat4<float> & transform, Bitmap & bitmap) {

    for(size_t i = 0; i < vertices.size(); i++) {
        vertices[i].position = transform * vertices[i].position;
    }

    // draw triangles
    for(size_t i = 0; i < indices.size(); i+= 3) {

        int indexOne = indices[i + 0];
        int indexTwo = indices[i + 1];
        int indexTre = indices[i + 2];

        drawTriangle(vertices[indexOne], vertices[indexTwo], vertices[indexTre], bitmap); // does clipping if needed
    }
}

//------------------------------------------------------------
void
RenderContext::clearDepthBuffer() {
    std::fill(std::begin(m_depthBuffer), std::end(m_depthBuffer), -1000); // fix : remove this magic number
}

/* PRIVATE */

//------------------------------------------------------------
bool
RenderContext::clipPolygonAxis(std::vector<Vertex> & vertices, std::vector<Vertex> & output, int axis) {
    clipPolygonAxisComponent(vertices, output, axis, 1.0f);
    vertices.clear();

    if(output.empty()) {
        return false; // all verts where outside the positive axis
    }

    clipPolygonAxisComponent(output, vertices, axis, -1.0f);
    output.clear();

    return !vertices.empty();
}

//------------------------------------------------------------
void
RenderContext::clipPolygonAxisComponent(std::vector<Vertex> & vertices, std::vector<Vertex> & output, int axis, float sign) {

    Vertex lastVertex = vertices[vertices.size() - 1];
    float  lastComp   = lastVertex.position[axis] * sign;
    bool   lastInside = lastComp <= lastVertex.position.w;

    for(int i = 0; i < vertices.size(); i++) {

        Vertex currVertex = vertices[i];
        float  currComp   = currVertex.position[axis] * sign;
        bool   currInside = currComp <= currVertex.position.w;
        
        if(currInside ^ lastInside) {
           float lerpStep = (lastVertex.position.w - lastComp) /
                           ((lastVertex.position.w - lastComp) -
                            (currVertex.position.w - currComp));

           output.push_back(lerp(lastVertex, currVertex, lerpStep));
        }

        if(currInside) {
            output.push_back(currVertex);
        }

        lastVertex = currVertex;
        lastComp = currComp;
        lastInside = currInside;
    }
}

//------------------------------------------------------------
void // vertices must be clipped before uing this function
RenderContext::fillTriangle(Vertex v1, Vertex  v2, Vertex v3, Bitmap & bitmap) {

    // change vectors from -1 ~ 1 space to 0 ~ screenWidth
    v1.position = m_screenSpaceTransform * v1.position;
    v2.position = m_screenSpaceTransform * v2.position;
    v3.position = m_screenSpaceTransform * v3.position;

    // @perf : avoid not needed matrix vector mult just do below
    //x' = x*halfWidth + halfWidth
    //y' = y*halfHeight + halfHeight

    djc_math::perspectiveDivide(v1.position);
    djc_math::perspectiveDivide(v2.position);
    djc_math::perspectiveDivide(v3.position); // perf : could be inlined.


    if(v3.getY() < v2.getY()) {
        std::swap(v3, v2);
    }

    if(v2.getY() < v1.getY()) {
        std::swap(v2, v1);
    }

    if(v3.getY() < v2.getY()) {
        std::swap(v3, v2);
    }

    float pointLineIntersect = (v2.position.x - v1.position.x) * 
                               (v3.position.y - v1.position.y) -
                               (v2.position.y - v1.position.y) * 
                               (v3.position.x - v1.position.x);

    bool isleftHanded = pointLineIntersect >= 0 ? true : false;

    scanTriangle(v1, v2, v3, isleftHanded, bitmap);
}

//------------------------------------------------------------
void // @perf : everything beyond this point should be 3D not 4D - no need to send a vec4 only need a vec3 because z is not needed send (x, y, w)
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

    auto currColour = left.colour;
    auto colourStep((right.colour - left.colour) / xDist);

    auto currTexCoord = left.texCoord;
    auto texCoordStep((right.texCoord - left.texCoord) / xDist);

    float currW = left.oneOverW;
    float wStep = (right.oneOverW - currW) / xDist;

    
    // perf : dont do perspective correction every pixel but every few pixels
    int row = m_width * y;
    for(float x = xMin; x < xMax; ++x) {

        if(m_depthBuffer[row + x] <  1.0 * currW) {
            m_depthBuffer[row + x] = 1.0 * currW;

            float z = 1.0f / currW;

            auto correctedTexColour = bitmap.getPixel((currTexCoord.x * z) * (bitmap.getWidthF() - 1.0f) + 0.5f,
                                                             (currTexCoord.y * z) * (bitmap.getHeightF() - 1.0f) + 0.5f);

            auto correctedColour = djc_math::Vec3<float>(currColour.x * z, currColour.y * z, currColour.z * z);                                    
        
           //auto finalColour = correctedColour * correctedTexColour;
            auto finalColour = correctedTexColour;

            setPixel(x, y, static_cast<unsigned char>(finalColour.z * 255.99f),
                           static_cast<unsigned char>(finalColour.y * 255.99f), 
                           static_cast<unsigned char>(finalColour.x * 255.99f));
        
        }

        // step all the things
        currColour   += colourStep;
        currTexCoord += texCoordStep;
        currW        += wStep;
    }
}

//------------------------------------------------------------
void // fix : call this function when screen size changes - need to account for scale
RenderContext::updateContextSize(float width, float height) {
    m_screenSpaceTransform = djc_math::createMat4ScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    Bitmap::resize(width, height);
}