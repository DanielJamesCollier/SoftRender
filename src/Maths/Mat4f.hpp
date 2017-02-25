#ifndef Mat4f_hpp
#define Mat4f_hpp

#include <cmath>

/*
    TODO
    - overloads
    - add matrix [] overload then change class to use it
*/

//--------------------
// [0]  [1]  [2]  [3] 
// [4]  [5]  [6]  [7] 
// [8]  [9]  [10] [11]
// [12] [13] [14] [15]
//---------------------

#include "Vec3.hpp" // move out of here into own class when starting matrix  * vec3 operations

namespace Maths {
    
    class Mat4f {
    public:  
        Mat4f(bool isIdentity);
        ~Mat4f() = default;

        // matrix create functions return a new matrix
        //--------------------------------------------------------------
        friend Mat4f createProjectionMatrix();
        friend Mat4f createModelMatrix(Vec3 const & position);
        friend Mat4f createModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale);

        // opperates on existing matrices by = 
        // overwrites previouse values
        //--------------------------------------------------------------
        friend void setIdentity(Mat4f & matrix);
        friend void setTranslation(Mat4f & matrix, Vec3 const & position);
        friend void setRotationX(Mat4f & matrix, float rotation);
        friend void setRotationY(Mat4f & matrix, float rotation);
        friend void setRotationZ(Mat4f & matrix, float rotation);
        friend void setScale(Mat4f & matrix, Vec3 const & scale);

        // opperates on existing matrices by +=
        // += to previouse values
        //--------------------------------------------------------------
        friend void translate(Mat4f & matrix, Vec3 const & position);
        friend void rotateX(Mat4f & matrix, float rotation);
        friend void rotateY(Mat4f & matrix, float rotation);
        friend void rotateZ(Mat4f & matrix, float rotation);
        friend void scale(Mat4f & matrix, Vec3 const & scale);

        // operator overloads
        //--------------------------------------------------------------
        friend Mat4f operator + (Mat4f const & lhs, Mat4f const & rhs);
        friend Mat4f operator + (Mat4f const & lhs, Vec3 const & rhs);
        //friend Mat4f operator + (Vec3 const & lhs, Mat4f const & rhs);

        friend Mat4f operator - (Mat4f const & lhs, Mat4f const & rhs);
        friend Mat4f operator - (Mat4f const & lhs, Vec3 const & rhs);
        //friend Mat4f operator - (Vec3 const & lhs, Mat4f const & rhs);

        friend Mat4f operator * (Mat4f const & lhs, Mat4f const & rhs);
        friend Mat4f operator * (Mat4f const & lhs, Vec3 const & rhs);
        //friend Mat4f operator * (Vec3 const & lhs, Mat4f const & rhs);

        friend Mat4f operator / (Mat4f const & lhs, Mat4f const & rhs);
        friend Mat4f operator / (Mat4f const & lhs, Vec3 const & rhs);
        //friend Mat4f operator / (Vec3 const & lhs, Mat4f const & rhs);

    private:
        float & operator [] (int index);

    private:
        float m_data[16];
    };
} /* Maths */
#include "Mat4f.inl" // contains all the friend free functions
#endif /* Mat4f_hpp */