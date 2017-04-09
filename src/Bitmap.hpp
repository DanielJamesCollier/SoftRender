#ifndef Bitmap_hpp
#define Bitmap_hpp

// my
#include "djc_math/Utils.hpp"
#include "djc_math/Vec3.hpp"
// std
#include <vector>

class Bitmap {
    using Buffer = std::vector<unsigned char>;
public:
    Bitmap(int width, int height);
    virtual ~Bitmap() = default;

    unsigned char & operator [] (int index);

    int getWidth() const;
    int getHeight() const;

    // get width as float
    float getWidthF() const;
    float getHeightF() const;

    Buffer & getBuffer();
    
    void setPixel(int x, int y, unsigned char b, unsigned char g, unsigned char r);
    djc_math::Vec3f getPixel(int x, int y);

    void clear();

    void resize(int width, int height);

    friend Bitmap createRandomBitmap(int width, int height);

protected:
    int m_width;
    int m_height;
    float m_widthF;
    float m_heightF;
    Buffer m_buffer;
};

inline Bitmap
createRandomBitmap(int width, int height) {
    Bitmap bMap(width, height);

    for(unsigned char & pixel : bMap.m_buffer) {
        pixel = djc_math::randUCBetween0N255();
    }

    return bMap;
}

#endif /* Bitmap_hpp */