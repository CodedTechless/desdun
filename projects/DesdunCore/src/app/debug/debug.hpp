#pragma once

#include <glew/glew.h>

#include <corelib/core.hpp>

namespace DesdunCore 
{

	struct LogMessage
	{
		std::string time;
		std::string type;
		std::string header;
		std::string contents;
	};

	class Debug
	{
	public:
		static std::string getTimeAsString();

		static void Log(const std::string& string, const std::string& type, const std::string& header);
		static void Log(const std::string& string, const std::string& header = "");

		static void Warn(const std::string& string, const std::string& header = "");
		static void Error(const std::string& string, const std::string& header = "");

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