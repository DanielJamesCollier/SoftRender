// matrix create functions return a new matrix
//--------------------------------------------------------------
namespace Maths {
    inline Mat4f 
    createProjectionMatrix(float fov) {
        return Mat4f(true); //todo
    }

    inline Mat4f 
    createModelMatrix(Vec3 const & position, Vec3 const & rotation, Vec3 const & scale) {
        Mat4f translationMat(true);
        translationMat[12] = position.getX();
        translationMat[13] = position.getY();
        translationMat[14] = position.getZ();

        Mat4f rotX(true);
        setRotationX(rotX, rotation.getX());
        Mat4f rotY(true);
        setRotationY(rotY, rotation.getY());
        Mat4f rotZ(true);
        setRotationZ(rotZ, rotation.getZ());

        Mat4f rotationMat(rotZ * rotY * rotX);

        Mat4f scaleMat(true);
        scaleMat[0]  = scale.getX();
        scaleMat[5]  = scale.getY();
        scaleMat[10] = scale.getZ();

        return scaleMat * translationMat * rotationMat;
    }

        // opperates on existing matrices by =
    //--------------------------------------------------------------

    inline void 
    setIdentity(Mat4f & matrix) {
        matrix[0]  = 1;  matrix[1]  = 0;  matrix[2]  = 0;  matrix[3]  = 0;
        matrix[4]  = 0;  matrix[5]  = 1;  matrix[6]  = 0;  matrix[7]  = 0;
        matrix[8]  = 0;  matrix[9]  = 0;  matrix[10] = 1;  matrix[11] = 0;
        matrix[12] = 0;  matrix[13] = 0;  matrix[14] = 0;  matrix[15] = 1;
    }

    inline void
    setTranslation(Mat4f & matrix, Vec3 const & position) {
        matrix[12] = position.getX();
        matrix[13] = position.getY();
        matrix[14] = position.getZ();
    }

    inline void
    setRotationX(Mat4f & matrix, float angle) {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        matrix[5]  =  cos;
        matrix[6]  =  sin;
        matrix[9]  = -sin;
        matrix[10] =  cos;
    }

    inline void
    setRotationY(Mat4f & matrix, float angle) {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        matrix[0] =  cos;
        matrix[2] = -sin;
        matrix[8] =  sin;
        matrix[8] =  cos;
    }

    inline void
    setRotationZ(Mat4f & matrix, float angle) {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        matrix[0] =  cos;
        matrix[1] =  sin;
        matrix[5] = -sin;
        matrix[6] =  cos;
    }

    inline void 
    setScale(Mat4f & matrix, Vec3 const & scale) {
        matrix[0]  = scale.getX();
        matrix[5]  = scale.getY();
        matrix[10] = scale.getZ();
    }

    // opperates on existing matrices by +=
    //--------------------------------------------------------------
    inline void
    translate(Mat4f & matrix, Vec3 const & position) {
        matrix[12] += position.getX();
        matrix[13] += position.getY();
        matrix[14] += position.getZ();
    }

    inline void
    rotateX(Mat4f & matrix, float angle) {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        matrix[5]  +=  cos;
        matrix[6]  +=  sin;
        matrix[9]  += -sin;
        matrix[10] +=  cos;
    }

    inline void
    rotateY(Mat4f & matrix, float angle) {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        matrix[0] +=  cos;
        matrix[2] += -sin;
        matrix[8] +=  sin;
        matrix[8] +=  cos;
    }

    inline void
    rotateZ(Mat4f & matrix, float angle) {
        float sin = std::sin(angle);
        float cos = std::cos(angle);
        matrix[0] +=  cos;
        matrix[1] +=  sin;
        matrix[5] += -sin;
        matrix[6] +=  cos;
    }

    inline void 
    scale(Mat4f & matrix, Vec3 const & scale) {
        matrix[0]  += scale.getX();
        matrix[5]  += scale.getY();
        matrix[10] += scale.getZ();
    }

    // operator overloads
    //--------------------------------------------------------------
    inline Mat4f
    operator + (Mat4f const & lhs, Mat4f const & rhs) {
        Mat4f matrix(false);

        return matrix;
    }

    inline Mat4f
    operator + (Mat4f const & lhs, Vec3 const & rhs) {
        Mat4f matrix(false);

        return matrix;
    }

    inline Mat4f
    operator * (Mat4f const & lhs, Mat4f const & rhs) {
        Mat4f matrix(false);

        auto offset = [](int x, int y) {
            return 4 * x + y;
        };

        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                matrix.m_data[offset(x,y)] = 0;
                for (int z = 0; z < 4; z++) {
                    matrix.m_data[offset(x,y)] += lhs.m_data[offset(x,y)] * rhs.m_data[offset(x,y)];
                }
            }
        }
        return matrix;
    }
}
