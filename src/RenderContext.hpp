#ifndef RenderContext_hpp
#define RenderContext_hpp

//std
#include <vector>

// my
#include "Maths/Vec3.hpp"
#include "Bitmap.hpp" 

class RenderContext : public Bitmap {
public:
    RenderContext(int width, int height);
    ~RenderContext() = default;

    void drawScanBuffer(int y, int xMin, int xMax);
    void fillShape(int yMin, int yMax);
    void fillTriangle(Maths::Vec3 v1, Maths::Vec3 v2, Maths::Vec3 v3);
    void scanConvertTriangle(Maths::Vec3 const & minY, Maths::Vec3 const & midY, Maths::Vec3 const & maxY, int handedness);

private:
    void scanConvertLine(Maths::Vec3 const & minY, Maths::Vec3 const &maxY, int handedness);

private:
    std::vector<int> m_scanBuffer;
};
#endif /* RenderContext_hpp */