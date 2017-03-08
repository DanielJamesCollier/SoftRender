#ifndef Edge_hpp
#define Edge_hpp

class Vertex;

class Edge final {
    friend class RenderContext;
public:
    Edge(Vertex minY, Vertex maxY);
    ~Edge() = default;

    void step();


    int m_yStart;
    int m_yEnd;
    float m_x;
	float m_xStep;
};
#endif /* Edge_hpp */