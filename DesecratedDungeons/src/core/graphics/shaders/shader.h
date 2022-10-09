#pragma once

#include <glm/glm.hpp>
#include <libraries.hpp>

namespace Desdun 
{

	struct ShaderSource 
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	enum class ShaderType 
	{
		None = 0,
		Vertex = 1,
		Fragment = 2
	};

	class Shader 
	{
	public:
		Shader() = default;
		Shader(const std::string& Path);
		~Shader();

		void Import(const std::string& Path);

		void Bind();
		void Unbind();

		uint GetRenderID() const { return RenderID; };

	public:
		void SetUniform(const std::string& Name, const Vector4& Value);
		void SetUniform(const std::string& Name, const Vector3& Value);
		void SetUniform(const std::string& Name, int Value);
		void SetUniform(const std::string& Name, int* Values, uint Size);
		void SetUniform(const std::string& Name, const Mat4& Matrix);

	private:
		uint RenderID = 0;
		std::string Path = "";

		std::unordered_map<std::string, int> UniformCache;
		uint GetUniformLocation(const std::string& Name);

		static ShaderSource Parse(const std::string& FilePath);
		static uint Compile(unsigned int Type, const std::string& SourceString);
		static uint Create(const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
	};
}