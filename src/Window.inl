template<int width, int height>
void Window::draw(MultiArray<Maths::Vec3, width, height> & pixels) {  
    auto index = 0;
    for (auto y = height - 1; y > 0; y--) { 
        for (auto x = 0; x < width; x++) {  
            Maths::Vec3 pixel = pixels(y, x);

            m_pixels[index + 0] = pixel.getZ(); // blue 
            m_pixels[index + 1] = pixel.getY(); // green
            m_pixels[index + 2] = pixel.getX(); // red
            m_pixels[index + 3] = SDL_ALPHA_OPAQUE;
            index+=4;
        }
    }
}