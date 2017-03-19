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

    // getters
    float getYStart() const;
    float getYEnd() const;

    // interpolant getters
    float getX() const;
    float getOneOverW() const;
    Maths::Vec3 const & getColour() const;
    Maths::Vec2 const & getTexCoord() const;

private:
    // edge range
    int m_yStart;
    int m_yEnd;

    /* interpolants */

    // x is used for drawing from one edge to another [leftEdge.x loop to rightEdge.x]
    float m_x; // interpolant
	float m_xStep; 

    // w is used for perspective correction of interpolants
    float m_oneOverW;
    float m_oneOverW_step;

    // colour
    Maths::Vec3 m_colour; // interpolant
    Maths::Vec3 m_colourStep;

    // texture coordinate
    Maths::Vec2 m_texCoord; // interpolant
    Maths::Vec2 m_texCoordStep;
  
};
#endif /* Edge_hpp */