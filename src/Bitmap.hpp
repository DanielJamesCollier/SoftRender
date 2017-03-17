#ifndef Bitmap_hpp
#define Bitmap_hpp

// my
#include "Maths/MathsUtils.hpp"

// std
#include <vector>

class Colour;

class Bitmap {
    using Buffer = std::vector<unsigned char>;
public:
    Bitmap(int width, int height);
    virtual ~Bitmap() = default;

    unsigned char & operator [] (int index);

    int getWidth() const;
    int getHeight() const;
    Buffer & getBuffer();
    
    void setPixel(int x, int y, Colour const & colour);
    Colour getPixel(int x, int y);

    void clear();

    friend Bitmap createRandomBitmap(int width, int height);

protected:
    int m_width;
    int m_height;
    Buffer m_buffer;
};

inline Bitmap
createRandomBitmap(int width, int height) {
    Bitmap bMap(width, height);

    for(unsigned char & pixel : bMap.m_buffer) {
        pixel = Maths::randUCBetween0N255();
    }

    return bMap;
}

#endif /* Bitmap_hpp */