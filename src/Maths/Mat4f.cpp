//std
#include <algorithm>

// my
#include "Mat4f.hpp"

namespace Maths {

//------------------------------------------------------------
Mat4f::Mat4f() {
    for(int i = 0; i < 16; i++) {
        m_data[i] = 0.0f; // todo change to ::fill
    }
}

//------------------------------------------------------------
float & 
Mat4f::operator [] (int index) {
    return m_data[index]; // todo change to size_t
}

//------------------------------------------------------------
float const & 
Mat4f::operator [] (int index) const {
    return m_data[index]; // todo change to size_t
}

} /* namespace Maths */