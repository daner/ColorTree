#include "Shader.h"
#include "../Filesystem.h"
#include <iostream>
#include <vector>

namespace ColorTree
{
    using namespace std;
    using namespace Filesystem;

    Shader::Shader() :
        programId{ 0 }
    {
    }

    Shader::Shader(string vertexFilename, string fragmentFilename) :
        programId{ 0 },
        vertexFilename{ vertexFilename },
        fragmentFilename{ fragmentFilename }
    {
        LoadShader();
    }

    Shader::~Shader()
    {
        UnloadShader();
    }

    void Shader::InitWithSourceFiles(string vertexFilename, string fragmentFilename)
    {
        this->vertexFilename = vertexFilename;
        this->fragmentFilename = fragmentFilename;
        UnloadShader();
        LoadShader();
    }

    void Shader::Bind() const
    {
        glUseProgram(programId);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::Reload()
    {
        UnloadShader();
        LoadShader();
    }

    GLuint Shader::ProgramId() const
    {
        return programId;
    }

    void Shader::LoadShader()
    {
        auto vertexSource = GetFileContents(GetPath("Resources/Shaders/" + vertexFilename));
        auto fragmentSource = GetFileContents(GetPath("Resources/Shaders/" + fragmentFilename));

        auto vertexString = vertexSource.c_str();
        int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexString, nullptr);
        glCompileShader(vertexShaderId);
        if (CheckCompilationStatus(vertexShaderId, vertexFilename) == GL_FALSE)
        {
            glDeleteShader(vertexShaderId);
            return;
        }

        auto fragmentString = fragmentSource.c_str();
        int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentString, nullptr);
        glCompileShader(fragmentShaderId);
        if (CheckCompilationStatus(fragmentShaderId, fragmentFilename) == GL_FALSE)
        {
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);
            return;
        }

        programId = glCreateProgram();
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);

        glLinkProgram(programId);

        glDetachShader(programId, vertexShaderId);
        glDetachShader(programId, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        if (CheckLinkStatus(programId) == GL_FALSE)
        {
            UnloadShader();
        }
    }

    void Shader::UnloadShader()
    {
        if (programId > 0) 
        {
            glUseProgram(0);
            glDeleteProgram(programId);
            programId = 0;
        }
    }

    int Shader::CheckCompilationStatus(int shader, string fileName) const
    {
        int isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            cout << "Failed to compile shader: " << fileName << endl << string(begin(errorLog), end(errorLog)) << endl;
        }
        return isCompiled;
    }

    int Shader::CheckLinkStatus(int program) const
    {
        int isLinked = 0;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            vector<GLchar> errorLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);
            cout << "Failed to link shader program: " << vertexFilename << " " << fragmentFilename << endl << string(begin(errorLog), end(errorLog)) << endl;
        }
        return isLinked;
    }
}
