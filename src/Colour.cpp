#include "Colour.hpp"

//------------------------------------------------------------
Colour::Colour(unsigned char b, unsigned char g, unsigned char r) :
    m_b(b)
,   m_g(g)
,   m_r(r) 
{
    // empty
}

//------------------------------------------------------------
unsigned char
Colour::getB() const {
    return m_b;
}

//------------------------------------------------------------
unsigned char 
Colour::getG() const {
    return m_g;
}

//------------------------------------------------------------
unsigned char 
Colour::getR() const {
    return m_r;
}

