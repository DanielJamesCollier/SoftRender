// my
#include "RenderContext.hpp"
#include "Edge.hpp"
#include "djc_math/djc_math.hpp"

// std
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstdint> // used for inline asm
#include <limits>

#define DEPTH_MAX -1000

/* PUBLIC */

//------------------------------------------------------------
RenderContext::RenderContext(int width, int height) 
:   Bitmap(width, height)
,   m_halfWidth(static_cast<float>(width) / 2.0f)
,   m_halfHeight(static_cast<float>(height) / 2.0f)
{   
    m_screenSpaceTransform = djc_math::createMat4ScreenSpaceTransform(m_halfWidth, m_halfHeight); 

    m_depthBuffer.resize(width * height);
    std::fill(std::begin(m_depthBuffer), std::end(m_depthBuffer), DEPTH_MAX);
}

//------------------------------------------------------------
void
RenderContext::drawMesh(std::vector<Vertex> vertices, djc_math::Mat4f & transform, Bitmap & bitmap) {  

    // transform vertices
    for(auto & vertex : vertices) {
        djc_math::transform(vertex.position, transform);
    }

    // draw triangles
    for(size_t i = 0; i < vertices.size(); i+= 3) {
        drawTriangle(vertices[i + 0],
                    vertices[i + 1],
                    vertices[i + 2],
                    bitmap);
    }    
}

//------------------------------------------------------------
void 
RenderContext::drawIndexedMesh(std::vector<Vertex> vertices, std::vector<unsigned int> const & indices, djc_math::Mat4f const & transform, Bitmap & bitmap) {
    for(auto & vertex : vertices) {
        djc_math::transform(vertex.position, transform);
    }

    // draw triangles
    for(size_t i = 0; i < indices.size(); i+= 3) {

        size_t index1 = indices[i + 0];
        size_t index2 = indices[i + 1];
        size_t index3 = indices[i + 2];

        drawTriangle(vertices[index1], 
                     vertices[index2],
                     vertices[index3], 
                     bitmap);   
    }
}

//------------------------------------------------------------
void
RenderContext::clearDepthBuffer() {
    std::fill(std::begin(m_depthBuffer), std::end(m_depthBuffer), DEPTH_MAX); // fix : remove this magic number
}

/* PRIVATE */

//------------------------------------------------------------
void
RenderContext::drawTriangle(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap) {

    auto isXinsidePosW = [](Vertex & vert) -> void {
        if(vert.position.x <= vert.position.w) {
            
        } else {
            std::cout << "vert went off screen: w " << vert.position.w << " x: " << vert.position.x << std::endl;
            vert.position.x = vert.position.w;
        }
    };

    // isXinsidePosW(v1);
    // isXinsidePosW(v2);
    // isXinsidePosW(v3);
    
    // * clipping * //

    struct VertexPacket {
        std::array<Vertex, 6> vertices;
        int count = 0;
    };

    VertexPacket packetOne;
    packetOne.vertices[0] = v1;
    packetOne.vertices[1] = v2;
    packetOne.vertices[2] = v3;
    packetOne.count = 3; // 3 vertices to start off

    VertexPacket packetTwo;

    // positive x clip
    //------------------------------------
    Vertex last = packetOne.vertices[packetOne.count - 1];
    bool lastInBounds = last.position.x <= last.position.w;
    
    for(int i = 0; i < packetOne.count; i++) {

        std::cout << "i: "  << i << std::endl;

        Vertex current = packetOne.vertices[i];
        bool currentInBounds = current.position.x <= current.position.w;

        std::cout << current.position.x << std::endl;

        if(lastInBounds ^ currentInBounds) {
            last.colour = djc_math::Vec3f(0,0,1);
            last.position.x = 0;
            packetTwo.vertices[packetTwo.count++] =  last;
        }

        if(currentInBounds) {
            packetTwo.vertices[packetTwo.count++] =  current;
        }

        last = current;
        lastInBounds = currentInBounds;
    }
    //------------------------------------

    std::cout << "count: " << packetTwo.count << std::endl;
    
    for(int i = 1; i < packetTwo.count - 1; i++) {
        drawTriangleWithinScreenBounds(packetTwo.vertices[0], packetTwo.vertices[i], packetTwo.vertices[i + 1], bitmap);
    }
}

//------------------------------------------------------------
void // vertices must be clipped before uing this function
RenderContext::drawTriangleWithinScreenBounds(Vertex v1, Vertex v2, Vertex v3, Bitmap & bitmap) {

    // clip space -> ndc space
    auto fromClipToNDC = [](Vertex & v) {
        v.position.x = v.position.x / v.position.w;
        v.position.y = v.position.y / v.position.w;
        v.position.z = v.position.z / v.position.w;
    };

    fromClipToNDC(v1);
    fromClipToNDC(v2);
    fromClipToNDC(v3);

    auto fromNDCToScreen = [this](Vertex & v) {
        v.position.x = (v.position.x + 1) * m_halfWidth;
        v.position.y = (v.position.y + 1) * m_halfHeight;
    };

    fromNDCToScreen(v1);
    fromNDCToScreen(v2);
    fromNDCToScreen(v3);
   
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

    } else {   

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

    float currDepth = left.depth;
    float depthStep = (right.depth - currDepth) / xDist;

    // perf todo : don't do perspective correction every pixel but every few pixels
    
    size_t row = m_width * y;
    for (float x = xMin; x < xMax; ++x) {
        if (m_depthBuffer[row + x] <  currDepth) {
            m_depthBuffer[row + x] = currDepth;

            float z = 1.0f / currW;
            int srcX = (int)((currTexCoord.x * z) * (float)(bitmap.getWidthF() - 1.0f));
            int srcY = (int)((currTexCoord.y * z) * (float)(bitmap.getHeightF() - 1.0f));
            
            auto correctedTexColour = bitmap.getPixel(srcX, srcY);

            auto correctedColour = djc_math::Vec3f(currColour.x * z, currColour.y * z, currColour.z * z);                                    
        
            //auto finalColour = correctedColour * correctedTexColour; // colour and texture
            //auto finalColour = correctedTexColour; // texture only
            auto finalColour = correctedColour; // colour only

            setPixel(x, y, static_cast<unsigned char>(finalColour.z * 255.99f),
                           static_cast<unsigned char>(finalColour.y * 255.99f), 
                           static_cast<unsigned char>(finalColour.x * 255.99f));
        
        }

        // step all the things
        currColour   += colourStep;
        currTexCoord += texCoordStep;
        currW        += wStep;
        currDepth    += depthStep;
    }
}

//------------------------------------------------------------
void // fix : call this function when screen size changes - need to account for scale
RenderContext::updateContextSize(float width, float height) {
    m_screenSpaceTransform = djc_math::createMat4ScreenSpaceTransform((float)width / 2.0f, (float)height / 2.0f);
    Bitmap::resize(width, height);
}