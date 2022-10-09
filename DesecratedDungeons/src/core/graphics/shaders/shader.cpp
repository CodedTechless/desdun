

#include <fstream>
#include <sstream>

#include <GL/glew.h>

#include <core/debug/debug.h>

#include "shader.h"

namespace Desdun 
{

    Shader::Shader(const std::string& Path)
    {
        Import(Path);
    }

    Shader::~Shader()
    {
        glDeleteProgram(RenderID);
    }

    void Shader::Bind()
    {
        glUseProgram(RenderID);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    unsigned int Shader::GetUniformLocation(const std::string& Name)
    {
        if (UniformCache.find(Name) != UniformCache.end())
            return UniformCache[Name];

        int Loc = glGetUniformLocation(RenderID, Name.c_str());
        if (Loc != -1)
            UniformCache[Name] = Loc;

        return Loc;
    }

    // Shader importation and compilation
    void Shader::Import(const std::string& ShaderPath)
    {
        ShaderSource Source = Parse(ShaderPath);
        uint Program = Create(Source.VertexSource, Source.FragmentSource);

        RenderID = Program;
        Path = ShaderPath;
    }

    void Shader::SetUniform(const std::string& Name, const Vector4& Value)
    {
        glUniform4f(GetUniformLocation(Name), Value.x, Value.y, Value.z, Value.w);
    }

    void Shader::SetUniform(const std::string& Name, const Vector3& Value)
    {
        glUniform3f(GetUniformLocation(Name), Value.x, Value.y, Value.z);
    }

    void Shader::SetUniform(const std::string& Name, int Value)
    {
        glUniform1i(GetUniformLocation(Name), Value);
    }

    void Shader::SetUniform(const std::string& Name, int* Values, uint Size)
    {
        glUniform1iv(GetUniformLocation(Name), Size, Values);
    }

    void Shader::SetUniform(const std::string& Name, const glm::mat4& Matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, &Matrix[0][0]);
    }

    ShaderSource Shader::Parse(const std::string& FilePath)
    {
        std::ifstream Stream(FilePath);

        std::string Line;
        std::stringstream ss[2];

        ShaderType Type = ShaderType::None;
        while (getline(Stream, Line))
        {
            if (Line.find("#shader") != std::string::npos)
            {
                if (Line.find("vertex") != std::string::npos)
                    Type = ShaderType::Vertex;
                else if (Line.find("fragment") != std::string::npos)
                    Type = ShaderType::Fragment;
            }
            else
            {
                ss[(int)Type] << Line << "\n";
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    uint Shader::Compile(unsigned int Type, const std::string& SourceString)
    {
        uint ShaderID = glCreateShader(Type);
        const char* Source = SourceString.c_str();

        glShaderSource(ShaderID, 1, &Source, nullptr);
        glCompileShader(ShaderID);

        int Result;
        glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);

        if (Result == GL_FALSE) 
        {
            int Length;
            glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &Length);

            char* Message = (char*)malloc(Length * sizeof(char));
            glGetShaderInfoLog(ShaderID, Length, &Length, Message);

            if (!Message)
                Debug::Error(std::string(Type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader failed to compile: [no error message]");
            else
                Debug::Error(std::string(Type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader failed to compile: " + std::string(Message));

            glDeleteShader(ShaderID);

            return 0;
        }

        return ShaderID;
    }

    unsigned int Shader::Create(const std::string& VertexShaderSource, const std::string& FragmentShaderSource)
    {
        uint Program = glCreateProgram();
        uint VertexShader = Compile(GL_VERTEX_SHADER, VertexShaderSource);
        uint FragmentShader = Compile(GL_FRAGMENT_SHADER, FragmentShaderSource);

        glAttachShader(Program, VertexShader);
        glAttachShader(Program, FragmentShader);
        glLinkProgram(Program);
        glValidateProgram(Program);

        glDeleteShader(VertexShader);
        glDeleteShader(FragmentShader);

        return Program;
    }
}