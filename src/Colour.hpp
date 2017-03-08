#ifndef Colour_hpp
#define Colour_hpp

class Colour final {
public:
    Colour(unsigned char b = 0, unsigned char  g = 0, unsigned char  r = 0); // defaulted to white;
    ~Colour() = default;

    unsigned char getG() const;
    unsigned char getB() const;
    unsigned char getR() const;

private:
    unsigned m_b, m_g, m_r;
};

#endif /* Colour_hpp */