#ifndef Mat4f_hpp
#define Mat4f_hpp

#include "Vec3.hpp"
#include "Vec4.hpp"

namespace Maths {
    
    class Mat4f {
    public:  
        Mat4f();
        //Mat4f(Mat4f & rhs) = default;
        //Mat4f(Mat4f && rhs) = default;
        ~Mat4f() = default;

        // matrix create functions return a new matrix
        //--------------------------------------------------------------
        friend Mat4f createProjectionMatrix(float fov, float near, float far, float aspect);
        friend Mat4f createIdentityMatrix();
        friend Mat4f createModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale);
        friend Mat4f createTranslationMatrix(Vec3 const & postion);
        friend Mat4f createRotationMatrix(Vec3 const & rotation);
        friend Mat4f createScaleMatrix(Vec3 const & scale);
        friend Mat4f createScreenSpaceTransform(float width, float height);

        // opperates on existing matrices by = 
        // overwrites previouse values
        //--------------------------------------------------------------
        friend void setIdentity(Mat4f & matrix);
        friend void setTranslation(Mat4f & matrix, Vec3 const & position);
        friend void setRotationX(Mat4f & matrix, float angle);
        friend void setRotationY(Mat4f & matrix, float angle);
        friend void setRotationZ(Mat4f & matrix, float angle);
        friend void setScale(Mat4f & matrix, Vec3 const & scale);

        // operator overloads
        //--------------------------------------------------------------
        friend Mat4f operator * (Mat4f & lhs, Mat4f & rhs);
        friend std::ostream & operator << (std::ostream & lhs, Mat4f const & rhs);

        //--
        friend Vec4 operator * (Mat4f & lhs, Vec4 const & rhs);
        friend Vec3 operator * (Mat4f & lhs, Vec3 const & rhs); 

    private:
        float & operator [] (int index);

    private:
        float m_data[16];
    };
} /* Maths */
#include "Mat4f.inl" // contains all the friend free functions
#endif /* Mat4f_hpp */



// transforms use column major
//--------------------
// [0]  [1]  [2]  [3] 
// [4]  [5]  [6]  [7] 
// [8]  [9]  [10] [11]
// [12] [13] [14] [15]
//---------------------
