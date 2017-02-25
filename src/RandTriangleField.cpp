#include "RandTriangleField.hpp"
#include "RenderContext.hpp"

//------------------------------------------------------------
RandTriangleField::RandTriangleField(RenderContext & renderContext) :
    m_renderContext(renderContext) 
{
    initTriangle();
}

//------------------------------------------------------------
void 
RandTriangleField::update(float delta) {
      for(int i = 0; i < m_trianglePoints.size(); i++) {
        // move the star in z
        m_trianglePoints[i].setZ(m_trianglePoints[i].getZ() - (0.001f * delta));

        // if star behind the camera respawn
        if (m_trianglePoints[i].getZ() < 0) {
            initTriangle();
        }
    }
}

//------------------------------------------------------------
void 
RandTriangleField::render() {
    m_renderContext.fillTriangle(m_trianglePoints[0], m_trianglePoints[1], m_trianglePoints[2]);
}

//------------------------------------------------------------
void 
RandTriangleField::initTriangle() {
    auto randF = [](int min, int max) -> float {
        return (double)rand() / ((double)RAND_MAX + 1); // double to prevent overflow
    };

    float randZ = randF(0,3) + 0.0001f;

    for(int i = 0; i < m_trianglePoints.size(); i++) {
        m_trianglePoints[i].setX(randF(0, 500));
        m_trianglePoints[i].setY(randF(0, 500));
        m_trianglePoints[i].setZ(randZ);
    }
}