// std
#include <iostream>

// my
#include "Bitmap.hpp"

//------------------------------------------------------------
Bitmap::Bitmap(int width, int height) :
    m_width(width)
,   m_height(height)
,   m_widthF(static_cast<float>(width))
,   m_heightF(static_cast<float>(height))
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
float
Bitmap::getWidthF() const {
    return m_widthF;
}

//------------------------------------------------------------
float
Bitmap::getHeightF() const {
    return m_heightF;
}

//------------------------------------------------------------
Bitmap::Buffer & 
Bitmap::getBuffer() {
    return m_buffer;
}

//------------------------------------------------------------
void 
Bitmap::setPixel(int x, int y, unsigned char b, unsigned char g, unsigned char r) {
    int index = (m_width * y + x) * 4;

    if(x < 0 || x > m_width - 1 || y < 0 || y > m_height - 1) return; // cleanup - probably should never be called - this could be an assert

    m_buffer[index + 0] = b;
    m_buffer[index + 1] = g;
    m_buffer[index + 2] = r;
    m_buffer[index + 3] = 255;
}

//------------------------------------------------------------
Maths::Vec3
Bitmap::getPixel(int x, int y) {
    int index = (m_width * y + x) * 4;
    return Maths::Vec3((float)m_buffer[index + 2] / 255.0f,  // r
                       (float)m_buffer[index + 1] / 255.0f,  // g
                       (float)m_buffer[index + 0] / 255.0f); // b
}

//------------------------------------------------------------
void 
Bitmap::clear() {
   std::fill(std::begin(m_buffer), std::end(m_buffer), 0);
}

//------------------------------------------------------------
void 
Bitmap::resize(int width, int height) {
    m_width   = width;
    m_height  = height;
    m_widthF  = static_cast<float>(width);
    m_heightF = static_cast<float>(height);
    m_buffer.resize(width * height * 4);
    clear();
}