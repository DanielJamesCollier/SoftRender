#ifndef Edge_hpp
#define Edge_hpp

class Vertex;

class Edge final {
   
public:
    Edge(Vertex minY, Vertex maxY);
    ~Edge() = default;

    void step();

    float getYStart() {
        return m_yStart;
    }

    float getYEnd() {
        return m_yEnd;
    }

    float getX() {
        return m_x;
    }

private:
    int m_yStart;
    int m_yEnd;

    float m_x;
	float m_xStep;
};
#endif /* Edge_hpp */