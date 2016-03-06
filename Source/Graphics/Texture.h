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

		void Init(int width, int height, glm::vec3 color);
		void UpdateColor(int offsetX, int offsetY, int width, int height, glm::vec3 color);

	private:
		GLuint textureId;
    };
}