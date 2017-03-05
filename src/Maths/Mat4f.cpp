//std
#include <algorithm>

// my
#include "Mat4f.hpp"

namespace Maths {

//------------------------------------------------------------
Mat4f::Mat4f() {
    for(int i = 0; i < 16; i++) {
        m_data[i] = 0.0f;
    }
}

//------------------------------------------------------------
float & 
Mat4f::operator [] (int index) {
    return m_data[index];
}

} /* namespace Maths */