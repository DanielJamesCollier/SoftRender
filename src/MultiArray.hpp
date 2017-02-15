#ifndef MultiArray_hpp
#define MultiArray_hpp

template<typename T, int width, int height>
class MultiArray
{
public:
    MultiArray();
    ~MultiArray();

    // access as 1D array
    T & operator() (int x);

    // access as 2D array - row major
    T & operator() (int row, int col);

    // returns the raw array
    T * getData();

private:
    T * m_data;
};
#include "MultiArray.inl"

#endif /* MultiArray_hpp */