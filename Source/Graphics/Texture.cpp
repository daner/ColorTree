#include "Texture.h"
#include <vector>

namespace ColorTree
{
    using namespace std;
    using namespace glm;

    Texture::Texture() :
        textureId{ 0 },
        target{ GL_TEXTURE_2D }
    {
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &textureId);
    }

    void Texture::Init(ivec2 size, vec3 color)
    {
        auto imageSize = size.x * size.y;

        vector<GLfloat> colorBuffer{};
        colorBuffer.reserve(imageSize * 3);

        for (auto i = 0; i < imageSize; i++)
        {
            colorBuffer.push_back(color.r);
            colorBuffer.push_back(color.g);
            colorBuffer.push_back(color.b);
        }

        glGenTextures(1, &textureId);

        glBindTexture(target, textureId);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexImage2D(target, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_FLOAT, colorBuffer.data());

        glBindTexture(target, 0);
    }

    void Texture::UpdateColor(ivec2 offset, ivec2 size, vec3 color) const
    {
        auto imageSize = size.x * size.y;

        vector<GLfloat> colorBuffer{};
        colorBuffer.reserve(imageSize * 3);

        for (auto i = 0; i < imageSize; i++)
        {
            colorBuffer.push_back(color.r);
            colorBuffer.push_back(color.g);
            colorBuffer.push_back(color.b);
        }

        glBindTexture(target, textureId);
        glTexSubImage2D(target, 0, offset.x, offset.y, size.x, size.y, GL_RGB, GL_FLOAT, colorBuffer.data());
        glBindTexture(target, 0);
    }

    GLuint Texture::Id() const
    {
        return textureId;
    }

    void Texture::Bind(GLenum texunit) const
    {
        glActiveTexture(texunit);
        glBindTexture(target, textureId);
    }

    void Texture::Unbind(GLenum texunit) const
    {
        glActiveTexture(texunit);
        glBindTexture(target, 0);
    }
}
