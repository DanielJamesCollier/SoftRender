#include "Bitmap.hpp"

//------------------------------------------------------------
Bitmap::Bitmap(int width, int height) :
    m_width(width)
,   m_height(height)
{
    m_buffer.reserve(width * height * 4);
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
int 
Bitmap::getComponents() const {
    return 4;
}

//------------------------------------------------------------
Bitmap::Buffer & 
Bitmap::getBuffer() {
    return m_buffer;
}

//------------------------------------------------------------
void 
Bitmap::setPixel(int x, int y, Colour const & colour) {
    int index = (m_width * y + x) * getComponents();
    m_buffer[index + 0] = colour.getB();
    m_buffer[index + 1] = colour.getG();
    m_buffer[index + 2] = colour.getR();
    m_buffer[index + 3] = 255;
}

//------------------------------------------------------------
void 
Bitmap::clear() {
    for(int i = 0; i < m_width * m_height * 4; i++) {
        m_buffer[i] = 0;
    }
}