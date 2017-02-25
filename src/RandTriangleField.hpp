#ifndef RandTriangleField_hpp
#define RandTriangleField_hpp

// std
#include <array>

// my includes
#include "Maths/Vec3.hpp"

class RenderContext;

class RandTriangleField final {
public:
    RandTriangleField(RenderContext & renderContext);
    ~RandTriangleField() = default;

    void update(float delta);
    void render();

private:
    void initTriangle();

private:
    std::array<Maths::Vec3, 3> m_trianglePoints;
    RenderContext & m_renderContext;
}; 
#endif /* RandTriangleField_hpp */