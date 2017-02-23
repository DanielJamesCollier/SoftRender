// c
#include <cstdlib>
#include <iostream>
#include <cmath>

// my
#include "RenderContext.hpp"
#include "StarField.hpp"
#include "Colour.hpp"

//------------------------------------------------------------
StarField::StarField(RenderContext & renderContext, float speed, float spread) :
    m_speed(speed)
,   m_spread(spread)
,   m_rContext(renderContext)
{
    // init the stars position
    for(int i = 0; i < m_stars.size(); i++) {
        initStar(i);
    }
}

//------------------------------------------------------------
void 
StarField::initStar(int index) {
    auto randF = []() -> float {
        return (double)rand() / ((double)RAND_MAX + 1); // double to prevent overflow
    };

    m_stars[index].setX(2 * (randF() - 0.5f) * m_spread);
    m_stars[index].setY(2 * (randF() - 0.5f) * m_spread);
    m_stars[index].setZ(randF() + 0.0001f);
}

//------------------------------------------------------------
void 
StarField::update(float delta) {
    for(int i = 0; i < m_stars.size(); i++) {
        // move the star in z
        m_stars[i].setZ(m_stars[i].getZ() - (m_speed * delta));

        // if star behind the camera respawn
        if (m_stars[i].getZ() < 0) {
            initStar(i);
        }
    }
}

//------------------------------------------------------------
void
StarField::render() {
    static const auto bWidth = m_rContext.getWidth();
    static const auto bHeight = m_rContext.getHeight();

    float halfWidth = m_rContext.getWidth() / 2.0f;
    float halfHeight = m_rContext.getHeight() / 2.0f;

    auto toRadians = [&](float input) {
        return 2 * 3.14159265359 * (input / 180); 
    };

    float tanHalfFOV = std::tan(toRadians(70.0f / 2.0f));

    for(int i = 0; i < m_stars.size(); i++) {
        int x = static_cast<int>(m_stars[i].getX() / (m_stars[i].getZ() * tanHalfFOV) * halfWidth + halfWidth);
        int y = static_cast<int>(m_stars[i].getY() / (m_stars[i].getZ() * tanHalfFOV) * halfHeight + halfHeight);

        if(x < 0 || x >= m_rContext.getWidth() || y < 0 || y >= m_rContext.getHeight()) {
            initStar(i);
        } else {
            m_rContext.setPixel(x, y, Colour(255, 255, 255));
        }
    }
}