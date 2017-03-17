// std
#include <cmath>

// my
#include "RenderContext.hpp"
#include "StarField.hpp"
#include "Colour.hpp"
#include "Maths/Maths.hpp"

//------------------------------------------------------------
StarField::StarField(RenderContext & renderContext, float speed, float spread) :
    m_speed(speed)
,   m_spread(spread)
,   m_rContext(renderContext)
{
    // init the stars position
    for(size_t i = 0; i < m_stars.size(); i++) {
        initStar(i);
    }
}

//------------------------------------------------------------
void 
StarField::update(float delta) {
    for(size_t i = 0; i < m_stars.size(); i++) {
        // move the star in z
        m_stars[i].z = m_stars[i].z - (m_speed * delta);

        // if star behind the camera respawn
        if (m_stars[i].z < 0) {
            initStar(i);
        }
    }
}

//------------------------------------------------------------
void
StarField::render() {
    float halfWidth = m_rContext.getWidth() / 2.0f;
    float halfHeight = m_rContext.getHeight() / 2.0f;

    float tanHalfFOV = std::tan(Maths::toRadians(120.0f / 2.0f));

    for(size_t i = 0; i < m_stars.size(); i++) {
        int x = static_cast<int>(m_stars[i].x / (m_stars[i].z * tanHalfFOV) * halfWidth + halfWidth);
        int y = static_cast<int>(m_stars[i].y / (m_stars[i].z * tanHalfFOV) * halfHeight + halfHeight);

        if(x < 0 || x >= m_rContext.getWidth() || y < 0 || y >= m_rContext.getHeight()) {
            initStar(i);
        } else {
            m_rContext.setPixel(x, y, Colour(255, 255, 255));
        }
    }
}

//------------------------------------------------------------
void 
StarField::initStar(size_t index) {
    m_stars[index].x = 2 * (Maths::randFBetweenZeroOne() - 0.5f) * m_spread;
    m_stars[index].y = 2 * (Maths::randFBetweenZeroOne() - 0.5f) * m_spread;
    m_stars[index].z =      Maths::randFBetweenZeroOne() + 0.0001f;
}