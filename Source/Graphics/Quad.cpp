#include "Quad.h"
#include <vector>

using namespace std;

namespace ColorTree
{
    Quad::Quad() :
        vaoId(0)
    {
    }

    Quad::~Quad()
    {
        glDeleteVertexArrays(1, &vaoId);
    }

    void Quad::Init()
    {
        Init(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f);
    }

    void Quad::Init(float left, float right, float bottom, float top, float distance)
    {
        vector<GLfloat> vertices{ left,  bottom, distance,
                                  left,  top,    distance,
                                  right, top,    distance,
                                  right, bottom, distance,
                                  left,  bottom, distance,
                                  right, top,    distance, };

        vector<GLfloat> uvs{ 0.0f, 1.0f,
                             0.0f, 0.0f,
                             1.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 1.0f,
                             1.0f, 0.0f };

        GLuint vbo[2];

        glGenVertexArrays(1, &vaoId);
        glBindVertexArray(vaoId);

        glGenBuffers(2, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        glDeleteBuffers(2, vbo);
    }

    void Quad::Draw() const
    {
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}
