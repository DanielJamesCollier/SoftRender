#ifndef Edge_hpp
#define Edge_hpp

// my
#include "djc_math/Vec2.hpp"
#include "djc_math/Vec3.hpp"

class Vertex;

class Edge final {
   
public:
    Edge(Vertex const & minY, Vertex const & maxY);
    ~Edge() = default;

    void step();

    float getYStart() const;
    float getYEnd()   const;

public:
    // scan line x and x step
    float       x; 
    float       m_xStep; 

    // 1.0 / w = used for perspective correct texture mapping
    float       oneOverW;
    float       m_oneOverW_step;

    // colour interpolation across triangle
    djc_math::Vec3f colour;
    djc_math::Vec3f m_colourStep;

    // texture coordinate interpolation across the triangle
    djc_math::Vec2f texCoord;
    djc_math::Vec2f m_texCoordStep;

    float depth;
    float m_depthStep;

private:
    // edge  y range
    int m_yStart;
    int m_yEnd;
};
#endif /* Edge_hpp */