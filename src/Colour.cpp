// my
#include "Colour.hpp"
#include "Maths/MathsUtils.hpp"

//------------------------------------------------------------
Colour::Colour(float b, float g, float r) :
    m_b(Maths::clamp(b, 0.0f, 1.0f))
,   m_g(Maths::clamp(g, 0.0f, 1.0f))
,   m_r(Maths::clamp(r, 0.0f, 1.0f)) 
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

Colour
Colour::operator += (Colour const & rhs) {
    m_b += rhs.m_b;
    m_g += rhs.m_g;
    m_r += rhs.m_r;
    return *this;
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

