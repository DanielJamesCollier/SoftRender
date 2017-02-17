#ifndef Bitmap_hpp
#define Bitmap_hpp

// std
#include <vector>

//my 
#include "Colour.hpp"

class Bitmap final {
    using Buffer = std::vector<unsigned char>;
public:
    Bitmap(int width, int height);
    ~Bitmap() = default;

    unsigned char & operator [] (int index);

    int getWidth() const;
    int getHeight() const;
    int getComponents() const;
    Buffer & getBuffer();
    
    void setPixel(int x, int y, Colour const & colour);

    void clear();

private:
    int m_width;
    int m_height;
    Buffer m_buffer;
};

#endif /* Bitmap_hpp */