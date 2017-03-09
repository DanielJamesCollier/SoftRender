#include "Colour.hpp"

//------------------------------------------------------------
Colour::Colour(float b, float g, float r) :
    m_b(b)
,   m_g(g)
,   m_r(r) 
{
    // empty
}

//------------------------------------------------------------
Colour
Colour::operator + (Colour const & rhs) {
    return Colour(m_b + rhs.m_b, m_g + rhs.m_g, m_r + rhs.m_r);
}

//------------------------------------------------------------
Colour 
Colour::operator - (Colour const & rhs) {
    return Colour(m_b - rhs.m_b, m_g - rhs.m_g, m_r - rhs.m_r);
}

//------------------------------------------------------------
Colour
Colour::operator * (Colour const & rhs) {
    return Colour(m_b * rhs.m_b, m_g * rhs.m_g, m_r * rhs.m_r);
}

//------------------------------------------------------------
Colour 
Colour::operator / (Colour const & rhs) {
    return Colour(m_b / rhs.m_b, m_g / rhs.m_g, m_r / rhs.m_r);
}

//------------------------------------------------------------
float
Colour::getB() const {
    return m_b;
}

//------------------------------------------------------------
float
Colour::getG() const {
    return m_g;
}

//------------------------------------------------------------
float
Colour::getR() const {
    return m_r;
}

//------------------------------------------------------------
unsigned char
Colour::getB_uc() const {
    return static_cast<unsigned char>(m_b * 255.999);
}

//------------------------------------------------------------
unsigned char
Colour::getG_uc() const {
    return static_cast<unsigned char>(m_g * 255.999);
}

//------------------------------------------------------------
unsigned char
Colour::getR_uc() const {
    return static_cast<unsigned char>(m_r * 255.999);
}

