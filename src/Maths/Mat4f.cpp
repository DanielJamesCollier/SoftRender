#include "Mat4f.hpp"

namespace Maths {

    Mat4f::Mat4f(bool isIdentity) {
        if(isIdentity) {
            m_data[0]  = 1;  m_data[1]  = 0;  m_data[2]  = 0;  m_data[3]  = 0;
            m_data[4]  = 0;  m_data[5]  = 1;  m_data[6]  = 0;  m_data[7]  = 0;
            m_data[8]  = 0;  m_data[9]  = 0;  m_data[10] = 1;  m_data[11] = 0;
            m_data[12] = 0;  m_data[13] = 0;  m_data[14] = 0;  m_data[15] = 1;
        } else {
            for(int i = 0; i < 16; i++) {
                m_data[i] = 0;
            }
        }
    }

    float & 
    Mat4f::operator [] (int index) {
        return m_data[index];
    }
}