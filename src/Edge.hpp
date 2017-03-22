#ifndef Edge_hpp
#define Edge_hpp

// my
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"

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
    Maths::Vec3 colour;
    Maths::Vec3 m_colourStep;

    // texture coordinate interpolation across the triangle
    Maths::Vec2 texCoord;
    Maths::Vec2 m_texCoordStep;

private:
    // edge  y range
    int m_yStart;
    int m_yEnd;
};
#endif /* Edge_hpp */