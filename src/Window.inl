 template<int width, int height>
    void Window::draw(MultiArray<Maths::Vec3, width, height> & pixels, int numSamples) {  
        auto index = 0;
        for (auto y = height - 1; y > 0; y--) { 
            for (auto x = 0; x < width; x++) {  
                Maths::Vec3 pixel = pixels(y, x);
                pixel /= static_cast<float>(numSamples);
                pixel = Maths::Vec3(sqrtf(pixel.getX()), sqrtf(pixel.getY()), sqrtf(pixel.getZ()));
            
                unsigned char r = static_cast<unsigned char>(255.99 * pixel.getX());
                unsigned char g = static_cast<unsigned char>(255.99 * pixel.getY());
                unsigned char b = static_cast<unsigned char>(255.99 * pixel.getZ());

                m_pixels[index + 0] = b; // blue 
                m_pixels[index + 1] = g; // green
                m_pixels[index + 2] = r; // red
                m_pixels[index + 3] = SDL_ALPHA_OPAQUE;
                index+=4;
            }
        }
        int error = SDL_UpdateTexture(m_renderTexture, NULL, &m_pixels[0], width * 4);
        SDL_RenderCopy( m_renderer, m_renderTexture, NULL, NULL );
        SDL_RenderPresent(m_renderer);
    }