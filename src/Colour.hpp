#ifndef Colour_hpp
#define Colour_hpp

class Colour final {
public:
    Colour(unsigned char b, unsigned char  g, unsigned char  r);
    ~Colour() = default;

    unsigned char getG() const;
    unsigned char getB() const;
    unsigned char getR() const;

private:
    unsigned m_b, m_g, m_r;
};

#endif /* Colour_hpp */