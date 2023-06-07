#pragma once

#include <include/desdun_core.hpp>
#include <include/glew/glew.h>

namespace Desdun 
{

	struct LogMessage
	{
		std::string Time;
		std::string Type;
		std::string Header;
		std::string Contents;
	};

	class Debug
	{
	public:
		static void Log(const std::string& String, const std::string& Type, const std::string& Header);
		static void Log(const std::string& String, const std::string& Header = "");

		static void Warn(const std::string& String, const std::string& Header = "");
		static void Error(const std::string& String, const std::string& Header = "");

		static void OpenGLMessage(GLenum Source, GLenum Type, GLuint ID, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam);
		static void GLFWMessage(int error, const char* msg);

		template<typename Func>
		static void DefineCommand(std::string CommandName, Func commandFunction)
		{
			Commands[CommandName] = commandFunction;
		}

		static std::vector<LogMessage>& GetMessageLog() { return MessageLog; };
	private:

		static std::unordered_map<std::string, std::function<void()>> Commands;
		static std::vector<LogMessage> MessageLog;
	};
}