#include "Vec3.hpp"

namespace Maths {
    /* RAII */
    //------------------------------------------------------------
    Vec3::Vec3(float x, float y, float z)
    :
        m_data{x,y,z}
    {
        // empty
    }

    /* getters */
    //------------------------------------------------------------
    float
    Vec3::getX() const {
        return m_data[0];
    }

    //------------------------------------------------------------
    float 
    Vec3::getY() const {
        return m_data[1];
    }

    //------------------------------------------------------------
    float 
    Vec3::getZ() const {
        return m_data[2];
    }

     /* setters */
    //------------------------------------------------------------
    void
    Vec3::setX(float x) {
        m_data[0] = x;
    }

    //------------------------------------------------------------
    void
    Vec3::setY(float y) {
        m_data[1] = y;
    }

    //------------------------------------------------------------
    void
    Vec3::setZ(float z) {
        m_data[2] = z;
    }

    /* vector operations */
    //------------------------------------------------------------
    float 
    Vec3::length() const {
        return std::sqrt(m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2]);
    }
    
    //------------------------------------------------------------
    float
    Vec3::length2() const {
        return m_data[0] * m_data[0] + m_data[1] * m_data[1] + m_data[2] * m_data[2];
    }
    
    //------------------------------------------------------------
    void 
    Vec3::normalise() {
        float len = length();
        m_data[0]   /= len;
        m_data[1]   /= len;
        m_data[2]   /= len;
    }

    //------------------------------------------------------------
    float 
    Vec3::dot(Vec3 const & vec) const {
        return m_data[0] * vec.m_data[0] + m_data[1] * vec.m_data[1] + m_data[2] * m_data[2];
    }

    //------------------------------------------------------------
    Vec3
    Vec3::cross(Vec3 const & vec) {
        auto x = (m_data[1] * vec.m_data[2]) - (m_data[2] * vec.m_data[1]);
        auto y = (m_data[2] * vec.m_data[0]) - (m_data[0] * vec.m_data[2]);
        auto z = (m_data[0] * vec.m_data[1]) - (m_data[1] * vec.m_data[0]);
        return Vec3(x,y,z);
    }

    /* unary operators */
    //------------------------------------------------------------
    Vec3 
    Vec3::operator + () const {
        return *this;
    }

    //------------------------------------------------------------
    Vec3 
    Vec3::operator - () const {
        return Vec3(-m_data[0], -m_data[1], -m_data[2]);
    }

    /* maths operators */
    //------------------------------------------------------------
    Vec3
    Vec3::operator + (Vec3 const & vec) {
        return Vec3(m_data[0] + vec.m_data[0], m_data[1] + vec.m_data[1], m_data[2] + vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator - (Vec3 const & vec) {
        return Vec3(m_data[0] - vec.m_data[0], m_data[1] - vec.m_data[1], m_data[2] - vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator * (Vec3 const & vec) {
        return Vec3(m_data[0] * vec.m_data[0], m_data[1] * vec.m_data[1], m_data[2] * vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator / (Vec3 const & vec) {
        return Vec3(m_data[0] / vec.m_data[0], m_data[1] / vec.m_data[1], m_data[2] / vec.m_data[2]);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator + (float scalar) {
        return Vec3(m_data[0] + scalar, m_data[1] + scalar, m_data[2] + scalar);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator - (float scalar) {
        return Vec3(m_data[0] - scalar, m_data[1] - scalar, m_data[2] - scalar);
    }

    //------------------------------------------------------------
    Vec3
    Vec3::operator * (float scalar) {
        return Vec3(m_data[0] * scalar, m_data[1] * scalar, m_data[2] * scalar);
    }


    //------------------------------------------------------------
    Vec3
    Vec3::operator / (float scalar) {
        return Vec3(m_data[0] / scalar, m_data[1] / scalar, m_data[2] / scalar);
    }

    /* Vec3 assignment operators */
    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator += (Vec3 const & vec) {
        m_data[0] += vec.m_data[0];
        m_data[1] += vec.m_data[1];
        m_data[2] += vec.m_data[2];
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator -= (Vec3 const & vec) {
        m_data[0] -= vec.m_data[0];
        m_data[1] -= vec.m_data[1];
        m_data[2] -= vec.m_data[2];
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator *= (Vec3 const & vec) {
        m_data[0] *= vec.m_data[0];
        m_data[1] *= vec.m_data[1];
        m_data[2] *= vec.m_data[2];
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator /= (Vec3 const & vec) {
        m_data[0] /= vec.m_data[0];
        m_data[1] /= vec.m_data[1];
        m_data[2] /= vec.m_data[2];
        return *this;
    }

    /* scalar assignment opperators */
    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator += (float scalar) {
        m_data[0] += scalar;
        m_data[1] += scalar;
        m_data[2] += scalar;
        return *this;
    }

    //------------------------------------------------------------
    Vec3 &
    Vec3::operator -= (float scalar) {
        m_data[0] -= scalar;
        m_data[1] -= scalar;
        m_data[2] -= scalar;
        return *this;
    }

    //------------------------------------------------------------
    Vec3 & 
    Vec3::operator *= (float scalar) {
        m_data[0] *= scalar;
        m_data[1] *= scalar;
        m_data[2] *= scalar;
        return *this;
    }

    //------------------------------------------------------------
    Vec3 &
    Vec3::operator /= (float scalar) {
        m_data[0] /= scalar;
        m_data[1] /= scalar;
        m_data[2] /= scalar;
        return *this;
    }
}