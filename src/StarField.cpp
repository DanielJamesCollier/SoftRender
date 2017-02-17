// c
#include <cstdlib>
#include <iostream>

// my
#include "StarField.hpp"
#include "Colour.hpp"

//------------------------------------------------------------
StarField::StarField(float speed, float spread) :
    m_speed(speed)
,   m_spread(spread)
{
    // init the stars position
    for(int i = 0; i < m_starsSOA.numStars; i++) {
        initStar(i);
    }
}

//------------------------------------------------------------
void 
StarField::initStar(int index) {

    auto randF = []() -> float {
        return (double)rand() / ((double)RAND_MAX + 1);
    };

    m_starsSOA.x[index] = 2 * (randF() - 0.5f) * m_spread;
    m_starsSOA.y[index] = 2 * (randF() - 0.5f) * m_spread;
    m_starsSOA.z[index] = randF() + 0.0001f;
}

//------------------------------------------------------------
void
StarField::updateAndRender(Bitmap & bitmap, float delta) {

    //render
    float halfWidth = bitmap.getWidth() / 2.0f;
    float halfHeight = bitmap.getHeight() / 2.0f;

    for(int i = 0; i < m_starsSOA.numStars; i++) {
        int x = static_cast<int>((m_starsSOA.x[i] / m_starsSOA.z[i]) * halfWidth + halfWidth);
        int y = static_cast<int>((m_starsSOA.y[i] / m_starsSOA.z[i]) * halfHeight + halfHeight);

        // move the star in z
         m_starsSOA.z[i] -= m_speed * delta;

        if (m_starsSOA.z[i] < 0) {
            initStar(i);
        }

        if(x < 0 || x >= bitmap.getWidth() || y < 0 || y >= bitmap.getHeight()) {
            initStar(i);
        } else {
            bitmap.setPixel(x, y, Colour(255, 255, 255));
            
        }
    }
}