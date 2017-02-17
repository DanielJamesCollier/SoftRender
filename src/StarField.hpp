#ifndef StarField_hpp
#define StarField_hpp

// std
#include <vector>

// my
#include "Bitmap.hpp"

struct Star {
    static const int numStars = 1000;
    float x[numStars];
    float y[numStars];
    float z[numStars];
};

class StarField final {
public:
  
public:
    StarField(float speed, float spread);
    ~StarField() = default;

    void updateAndRender(Bitmap & bitmap, float delta);


private:
    void initStar(int index);

private:
    Star m_starsSOA;
    float m_speed;
    float m_spread;
};
#endif /* StarField_hpp */