#ifndef Bitmap_hpp
#define Bitmap_hpp

// std
#include <vector>
#include <iostream>

class Colour;

class Bitmap {
    using Buffer = std::vector<unsigned char>;
public:
    Bitmap(int width, int height);
    virtual ~Bitmap() {
          std::cout << "bitmap dtor" << std::endl;    
    }

    unsigned char & operator [] (int index);

    int getWidth() const;
    int getHeight() const;
    Buffer & getBuffer();
    
    void setPixel(int x, int y, Colour const & colour);

    void clear();

protected:
    int m_width;
    int m_height;
    Buffer m_buffer;
};

#endif /* Bitmap_hpp */