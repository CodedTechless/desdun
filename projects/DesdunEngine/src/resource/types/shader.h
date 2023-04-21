#pragma once

#include <glm/glm.hpp>
#include <core_lib.hpp>

#include <resource/resource.hpp>

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

	class Shader : public Resource
	{
	public:
		Shader() = default;

		void load() override;
		void unload() override;

		void bind();
		void unbind();

		uint getRenderID() const { return RenderID; };

	public:
		void setUniform(const std::string& name, const Vector4& Value);
		void setUniform(const std::string& name, const Vector3& Value);
		void setUniform(const std::string& name, int Value);
		void setUniform(const std::string& name, int* Values, uint Size);
		void setUniform(const std::string& name, const Mat4& Matrix);

	private:
		uint RenderID = 0;

		std::unordered_map<std::string, int> UniformCache;
		uint getUniformLocation(const std::string& Name);

		static ShaderSource Parse(const std::string& FilePath);
		static uint Compile(unsigned int Type, const std::string& SourceString);
		static uint Create(const std::string& VertexShaderSource, const std::string& FragmentShaderSource);

		friend class Resource;
	};
}