
namespace djc_math {

//-------------------
/*      Mat3X       */
//-------------------

// creates new

//------------------------------------------------------------
template<typename T> inline Mat3X<T>
createMat3XIdentityMatrix() {
    return Mat3X<T>(std::array<T, 9> {{1, 0, 0,
                                      0, 1, 0,
                                      0, 0, 1}});
}

//------------------------------------------------------------
template<typename T> inline Mat3X<T>
createMat3XRotationMatrix(Vec3X<T> const & rotation) {

    T xSin = std::sin(rotation.x);
    T xCos = std::cos(rotation.x);

    T ySin = std::sin(rotation.y);
    T yCos = std::cos(rotation.y);

    T zSin = std::sin(rotation.z);
    T zCos = std::cos(rotation.z);
    
    Mat3X<T> rotX(std::array<T, 9> {{
        1,     0,    0,
        0,  xCos, xSin,
        0, -xSin, xCos,
    }});

    Mat3X<T> rotY(std::array<T, 9>{{
        yCos, 0, -ySin,
           0, 1,     0,
        ySin, 0,  yCos
    }});

    Mat3X<T> rotZ(std::array<T, 9>{{
         zCos, zSin, 0,
        -zSin, zCos, 0,
            0,   0,  1
    }});
   
    return rotX * rotY * rotZ;
}

// use existing

//-------------------
/*      Mat4X       */
//-------------------

// create new

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XIdentityMatrix() {
    return Mat4X<T>(std::array<T, 16>{{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XTranslationMatrix(Vec3X<T> const & vec) {
    return Mat4X<T>(std::array<T, 16>{{
        1, 0, 0, vec.x,
        0, 1, 0, vec.y,
        0, 0, 1, vec.z,
        0, 0, 0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XRotationMatrix(Vec3X<T> const & rotation) {
    T xSin = std::sin(rotation.x);
    T xCos = std::cos(rotation.x);

    T ySin = std::sin(rotation.y);
    T yCos = std::cos(rotation.y);

    T zSin = std::sin(rotation.z);
    T zCos = std::cos(rotation.z);

    // perf : change this to Mat3X then put into Mat4X on return

    Mat4X<T> rotX(std::array<T, 16>{{
        1,     0,    0, 0,
        0,  xCos, xSin, 0,
        0, -xSin, xCos, 0,
        0,     0,    0, 1
    }});

    Mat4X<T> rotY(std::array<T, 16>{{
        yCos, 0, -ySin, 0,
           0, 1,     0, 0,
        ySin, 0,  yCos, 0,
           0, 0,     0, 1
    }});

    Mat4X<T> rotZ(std::array<T, 16>{{
         zCos, zSin, 0, 0,
        -zSin, zCos, 0, 0,
            0,    0, 1, 0,
            0,    0, 0, 1
    }});

    return rotX * rotY * rotZ;
}

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XScaleMatrix(Vec3X<T> const & vec) {
     return Mat4X<T>(std::array<T, 16>{{
        vec.x,     0,     0, 0,
            0, vec.y,     0, 0,
            0,     0, vec.z, 0,
            0,     0,     0, 1
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XModelMatrix(Vec3X<T> const & position, Vec3X<T> const & rotation, Vec3X<T> const & scale) {
    Mat4X<T> _translation = createMat4XTranslationMatrix<T>(position);
    Mat4X<T> _rotation    = createMat4XRotationMatrix<T>(rotation);
    Mat4X<T> _scale       = createMat4XScaleMatrix<T>(scale);

    return _translation * _rotation * _scale;
}

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XProjectionMatrix(float fov, float near, float far, float aspect) {
    T range = std::tan(fov / 2.0f) * near;
    T Sx    = (2 * near) / (range * aspect + range * aspect);
    T Sy    = near / range;
    T Sz    = -(far + near) / (far - near);
    T Pz    = -(2 * far * near) / (far - near);

    return Mat4X<T>(std::array<T, 16>{{
        Sx, 0,  0,  0,
        0, Sy,  0,  0,
        0,  0, Sz, -1,
        0,  0, Pz,  0
    }});
}

//------------------------------------------------------------
template<typename T> inline Mat4X<T>
createMat4XScreenSpaceTransform(float halfWidth, float halfHeight) {
    return Mat4X<T>(std::array<T, 16>{{
               halfWidth,                 0, 0, 0,
                       0,       -halfHeight, 0, 0,
                       0,                 0, 1, 0,
        halfWidth - 0.5f, halfHeight - 0.5f, 0, 1
    }});
}

// use existing

//------------------------------------------------------------
template<typename T> inline void 
setMat4XIdentity(Mat4X<T> & matrix) {
    matrix = Mat4X<T>(std::array<T, 16>{{ 
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    }});
}

} /* namespace djc_math */