#pragma once
#include <GL/glew.h>

namespace ColorTree
{
	class Quad
	{
	public:
		Quad();
		~Quad();

		void Init();
		void Draw();

	private:
		GLuint vaoId;
	};
}