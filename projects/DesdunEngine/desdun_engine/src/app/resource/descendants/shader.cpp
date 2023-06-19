

#include <fstream>
#include <sstream>

#include <desdun_engine/include/glew/glew.h>

#include <desdun_engine/src/app/debug/debug.h>

#include "shader.hpp"

namespace Desdun 
{

    void Shader::bind()
    {
        glUseProgram(internalId);
    }

    void Shader::unbind()
    {
        glUseProgram(0);
    }

    uint Shader::getUniformLocation(const String& Name)
    {
        if (uniformCache.find(Name) != uniformCache.end())
        {
            return uniformCache[Name];
        }

        int location = glGetUniformLocation(internalId, Name.c_str());
        if (location != -1)
        {
            uniformCache[Name] = location;
        }

        return location;
    }

    uint Shader::getShaderType(const String& id)
    {
        uint t = GL_NONE;

        if (id == "vertex")             t = GL_VERTEX_SHADER;
        else if (id == "tess_control")  t = GL_TESS_CONTROL_SHADER;
        else if (id == "geometry")      t = GL_GEOMETRY_SHADER;
        else if (id == "fragment")      t = GL_FRAGMENT_SHADER;
        else if (id == "compute")       t = GL_COMPUTE_SHADER;
        else
        {
            throw InvalidShaderTypeException(id);
        }
        
        return t;
    }

    // Shader importation and compilation
    void Shader::load()
    {
        std::ifstream stream(getPath());
        json jsonObject;

        stream >> jsonObject;

        internalId = glCreateProgram();

        List<uint> shaders = {};

        for (auto& object : jsonObject.items())
        {
            uint shaderType = getShaderType(object.key());

            // get the path and transform it
            String pathRaw = object.value().get<String>();
            String pathTrans = transformPath(pathRaw);

            // load the source
            std::ifstream stream(pathTrans);
            std::stringstream buffer;
            buffer << stream.rdbuf();

            // compile as the type and attach it to the program
            uint shaderId = compileAs(shaderType, buffer.str());
            glAttachShader(internalId, shaderId);
            
            // save the id so we can clean up afterwards
            shaders.push_back(shaderId);
            dd_log_fh("compiled {} shader {}", getPath(), object.key(), pathRaw);
        }

        glLinkProgram(internalId);
        glValidateProgram(internalId);

        for (uint shaderId : shaders)
        {
            glDeleteShader(shaderId);
        }

        loaded = true;
    }

    void Shader::unload()
    {
        glDeleteProgram(internalId);

        loaded = false;
    }

    void Shader::set(const std::string& key, const Vector4 value)
    {
        bind();
        glUniform4f(getUniformLocation(key), value.x, value.y, value.z, value.w);
    }

    void Shader::set(const std::string& key, const Vector3 value)
    {
        bind();
        glUniform3f(getUniformLocation(key), value.x, value.y, value.z);
    }

    void Shader::set(const std::string& key, int value)
    {
        bind();
        glUniform1i(getUniformLocation(key), value);
    }

    void Shader::set(const std::string& key, int* values, uint size)
    {
        bind();
        glUniform1iv(getUniformLocation(key), size, values);
    }

    void Shader::set(const std::string& key, const Mat4 mat)
    {
        bind();
        glUniformMatrix4fv(getUniformLocation(key), 1, GL_FALSE, &mat[0][0]);
    }

    uint Shader::compileAs(uint shaderType, const String& source)
    {
        uint shader = glCreateShader(shaderType);
        const char* sourceRaw = source.c_str();

        glShaderSource(shader, 1, &sourceRaw, nullptr);
        glCompileShader(shader);

        int res;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &res);

        if (res == GL_FALSE) 
        {
            int len;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

            char* message = (char*)malloc(len * sizeof(char));
            glGetShaderInfoLog(shader, len, &len, message);
            glDeleteShader(shader);

            throw ShaderCompilationException(std::to_string(shaderType), message != 0 ? message : "unknown");
        }

        return shader;
    }
}