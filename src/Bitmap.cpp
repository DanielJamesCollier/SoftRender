// std
#include <iostream>

// my
#include "Bitmap.hpp"
#include "Colour.hpp"

//------------------------------------------------------------
Bitmap::Bitmap(int width, int height) :
    m_width(width)
,   m_height(height)
{
    m_buffer.resize(width * height * 4);
    clear();
}

//------------------------------------------------------------
unsigned char &
Bitmap::operator[] (int index) {
    return m_buffer[index];
}

//------------------------------------------------------------
int
Bitmap::getWidth() const {
    return m_width;
}

//------------------------------------------------------------
int 
Bitmap::getHeight() const {
    return m_height;
}

//------------------------------------------------------------
Bitmap::Buffer & 
Bitmap::getBuffer() {
    return m_buffer;
}

//------------------------------------------------------------
void // fix: x and y should be bounded 
Bitmap::setPixel(int x, int y, Colour const & colour) {
    int index = (m_width * y + x) * 4;

    if(x < 0 || x > m_width - 1 || y < 0 || y > m_height - 1) return; // cleanup - probably should never be called - this could be an assert

    m_buffer[index + 0] = colour.getB_uc();
    m_buffer[index + 1] = colour.getG_uc();
    m_buffer[index + 2] = colour.getR_uc();
    m_buffer[index + 3] = 255;
}

//------------------------------------------------------------
Colour
Bitmap::getPixel(int x, int y) {
    int index = (m_width * y + x) * 4;

    if(index > m_width * m_height * 4) {
        return Colour();
    } else {
        float b = (float)m_buffer[index + 0] / 255.0f;
        float g = (float)m_buffer[index + 1] / 255.0f;
        float r = (float)m_buffer[index + 2] / 255.0f;

        // std::cout << "b: " << b << std::endl;
        // std::cout << "g: " << g << std::endl;
        // std::cout << "r: " << r << std::endl;
    
        return Colour(b,g,r);
    }
}

//------------------------------------------------------------
void 
Bitmap::clear() {
   std::fill(std::begin(m_buffer), std::end(m_buffer), 0);
}