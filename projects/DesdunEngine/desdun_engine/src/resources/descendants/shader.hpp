#pragma once

#include <desdun_engine/include/glm/glm.hpp>
#include <desdun_engine/include/ddlib/core.hpp>

#include <desdun_engine/src/resources/resource.hpp>

namespace Desdun 
{

	class InvalidShaderTypeException : public virtual Exception
	{
	public:
		InvalidShaderTypeException(const String& typeName)
			: Exception(std::format("{} is not a valid shader type.", typeName)) {};
	};

	class ShaderCompilationException : public virtual Exception
	{
	public:
		ShaderCompilationException(const String& typeName, const String& message) 
			: Exception(std::format("failed to compile {} shader:\n{}", typeName, message)) {};
	};

	class Shader : public Resource
	{
	public:
		Shader() = default;

		void load() override;
		void unload() override;

		void bind();
		void unbind();

		uint getInternalId() const { return internalId; };

		void set(const String& key, const Vector4 value);
		void set(const String& key, const Vector3 value);
		void set(const String& key, const Vector2 value);
		void set(const String& key, int value);
		void set(const String& key, int* ptr, uint size);
		void set(const String& key, const Mat4 mat);

	private:
		uint internalId = 0;

		Map<String, String> sources = {};
		Map<String, int> uniformCache = {};

		uint getUniformLocation(const String& Name);

		static uint compileAs(uint shaderType, const String& src);
		static uint getShaderType(const String& id);

		friend class Resource;
	};
}