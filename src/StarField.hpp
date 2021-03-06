#ifndef StarField_hpp
#define StarField_hpp

// std
#include <array>

// my includes
#include "djc_math/Vec3.hpp"

// my defines
#define NUM_STARS 20000

class RenderContext;

class StarField final {
public:
    StarField(RenderContext & renderContext, float speed, float spread);
    ~StarField() = default;

    void update();
    void render();

private:
    void initStar(size_t index);

private:
    float m_speed;
    float m_spread;
    std::array<djc_math::Vec3f, NUM_STARS> m_stars;
    RenderContext & m_rContext;
};
#endif /* StarField_hpp */