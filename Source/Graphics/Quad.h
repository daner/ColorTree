#pragma once
#include <GL/glew.h>

namespace ColorTree
{
	class Quad
	{
	public:
		Quad();
		~Quad();

        Quad(const Quad& other) = delete;
        Quad(Quad&& other) = delete;
        Quad& operator=(const Quad& other) = delete;
        Quad& operator=(Quad&& other) = delete;

		void Init();
        void Init(float left, float right, float bottom, float top, float distance);
		void Draw() const;

	private:
		GLuint vaoId;
	};
}