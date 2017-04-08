namespace djc_math {

//------------------------------------------------------------
inline constexpr float 
toRadians(float degrees) {
    return (degrees * PI) / 180;
}

//------------------------------------------------------------
inline float 
randFBetweenZeroOne() {
    return (double)rand() / ((double)RAND_MAX + 1);
}

//------------------------------------------------------------
inline unsigned char 
randUCBetween0N255() {
    return static_cast<unsigned char>(rand()%(255 + 1));
}

//------------------------------------------------------------
inline float
normalise(float valToNormalise, float min, float max) {
    return (valToNormalise - min) / (max - min);
}

//------------------------------------------------------------
template <typename T>
inline T lerp(T v0, T v1, float t) {
    return (1 - t) * v0 + t * v1;
}

//------------------------------------------------------------
template<typename T>
inline T clamp(T v, T low, T hi) {
    if(v < low) {
        return low;
    } else if(v > hi){
        return hi;
    }
    return v;
}

} /* namespace djc_math */