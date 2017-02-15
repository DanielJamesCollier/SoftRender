template<typename T, int width, int height> 
MultiArray<T, width, height>::MultiArray() {
    m_data = new T[width * height];

    if(m_data == 0) {
        std::cout << "multi array failed: out of memory" << std::endl;
        exit(-1);
    }
}

template<typename T, int width, int height>
MultiArray<T, width, height>::~MultiArray() {
    delete [] m_data; 
}

template<typename T, int width, int height>
T &
MultiArray<T, width, height>::operator() (int x) {
    return m_data[x];
}

template<typename T, int width, int height>
T &
MultiArray<T, width, height>::operator() (int row, int col) {
    return m_data[width * row + col];
}

template<typename T, int width, int height>
T * 
MultiArray<T, width, height>::getData() {
    return m_data;
}

