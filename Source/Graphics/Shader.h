#pragma once
#include <GL/glew.h>
#include <string>


namespace ColorTree
{
    class Shader
    {
    public:
        Shader();
        Shader(std::string vertexFilename, std::string fragmentFilename);
        ~Shader();

        Shader(Shader &&other) = delete;
        Shader &operator=(Shader &&other) = delete;
        Shader(const Shader &other) = delete;
        Shader &operator=(const Shader &other) = delete;

        void InitWithSourceFiles(std::string vertexFilename, std::string fragmentFilename);

        void Bind() const;
        void Unbind() const;

        void Reload();

        GLuint ProgramId() const;

    private:

        void LoadShader();
        void UnloadShader();

        int CheckCompilationStatus(int shader, std::string fileName) const;
        int CheckLinkStatus(int program) const;

        std::string vertexFilename;
        std::string fragmentFilename;

        GLuint programId;
    };
}