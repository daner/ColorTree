#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ColorTree
{
    class Texture
    {
	public:
		Texture();
		~Texture();

        Texture(Texture&& other) = delete;
        Texture& operator=(Texture&& other) = delete;
        Texture(const Texture& other) = delete;
        Texture& operator=(const Texture& other) = delete;

		void Init(glm::ivec2 size, glm::vec3 color);
		void UpdateColor(glm::ivec2 offset, glm::ivec2 size, glm::vec3 color) const;

        GLuint Id() const;
        void Bind(GLenum texunit) const;
        void Unbind(GLenum texunit) const;

	private:
		GLuint textureId;
        GLenum target;
    };
}