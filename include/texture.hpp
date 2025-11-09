#pragma once
#include <string>

class Texture
{
public:
    Texture(const char *filePath);
    ~Texture();

    unsigned int GetTexture() const { return m_texture; }

private:
    unsigned int m_texture;
    int m_width, m_height, m_nrChannels;
    unsigned char *m_imageData;
};