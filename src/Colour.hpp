#ifndef Colour_hpp
#define Colour_hpp

#include <ostream>

/*
    - float colours are stored in the range from 0 - 1
    - if colour is needed the range of 0 - 255 then use the unsigned char getters
*/

class Colour final {
public:
    explicit Colour(float b = 0.0f, float g = 0.0f, float r = 0.0f);
    ~Colour() = default;

    Colour operator + (Colour const & rhs);
    Colour operator - (Colour const & rhs);
    Colour operator * (Colour const & rhs);
    Colour operator / (Colour const & rhs);
    Colour operator += (Colour const & rhs);

    float getG() const;
    float getB() const;
    float getR() const;

    unsigned char getG_uc() const;
    unsigned char getB_uc() const;
    unsigned char getR_uc() const;

    friend Colour operator * (float lhs, Colour const & rhs);
    friend std::ostream & operator << (std::ostream & lhs, Colour const & rhs);

private:
    float m_b, m_g, m_r;
};

inline Colour operator * (float lhs, Colour const & rhs) {
    return Colour(lhs * rhs.m_b, lhs * rhs.m_g, lhs * rhs.m_r);
}

//------------------------------------------------------------
inline std::ostream & 
operator << (std::ostream & lhs, Colour const & rhs) {
    lhs << "Colour(b: " << rhs.m_b << ", g: " << rhs.m_g << " r: " << rhs.m_r << ")";
    return lhs;
}

#endif /* Colour_hpp */

// + - * /// needed for lerp

// add all others