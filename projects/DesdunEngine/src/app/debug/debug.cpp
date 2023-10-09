
#include <ctime>
#include <chrono>
#include <iostream>

#include "debug.h"

namespace Desdun
{
	std::vector<LogMessage> Debug::MessageLog = {};

	std::string Debug::getTimeAsString()
	{
		const time_t TimeNow = time(nullptr);
		struct tm Time;

		localtime_s(&Time, &TimeNow);

		auto hour = std::to_string(Time.tm_hour);
		auto minute = std::to_string(Time.tm_min);
		auto second = std::to_string(Time.tm_sec);

		if (hour.length() == 1)
			hour = "0" + hour;
		if (minute.length() == 1)
			minute = "0" + minute;
		if (second.length() == 1) 
			second = "0" + second;

		//TODO: fix this ugly ass shit wtf is this

		using namespace std::chrono;
		uint64_t milli_epoch = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
		).count();

		auto highres = (double_t)milli_epoch / 1000.0;
		auto sec = std::floor(highres);
		auto milli = std::to_string((uint64_t)((highres - sec) * 1000.0));

		if (milli.length() == 1)
		{
			milli = "00" + milli;
		}
		else if (milli.length() == 2)
		{
			milli = "0" + milli;
		}

		return std::format("{}:{}:{}.{}", hour, minute, second, milli);
	}

	void Debug::Log(const std::string& string, const std::string& type, const std::string& header)
	{
		std::string finalHeader = "";
		if (header != "")
		{
			finalHeader = std::format(" {} >", header);
		}

		std::string timeString = Debug::getTimeAsString();

		std::cout << std::format("[{}][{}]{} {}", timeString, type, finalHeader, string) << std::endl;
		MessageLog.push_back({ timeString, type, header, string });
	}

	void Debug::Log(const std::string& String, const std::string& Header)
	{
		Log(String, "INFO", Header);
	}

	void Debug::Warn(const std::string& String, const std::string& Header)
	{
		Log(String, "WARN", Header);
	}

	void Debug::Error(const std::string& String, const std::string& Header)
	{
		Log(String, "ERROR", Header);
	}

	void Debug::GLFWMessage(int error, const char* msg)
	{
		std::cerr << " [" + std::to_string(error) + "] " + std::string(msg) + '\n' << std::endl;
	}

	void Debug::OpenGLMessage(GLenum Source, GLenum Type, GLuint ID, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam)
	{
		std::string _source, _type, _severity;

		switch (Source) {
		case GL_DEBUG_SOURCE_API:
			_source = "API";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			_source = "WINDOW";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			_source = "SHADER";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			_source = "THIRD PARTY";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			_source = "APPLICATION";
			break;

		case GL_DEBUG_SOURCE_OTHER:
			_source = "UNKNOWN";
			break;

		default:
			_source = "UNKNOWN";
			break;
		}

		switch (Type) {
		case GL_DEBUG_TYPE_ERROR:
			_type = "ERROR";
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			_type = "DEPRECATED";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			_type = "UNDEFINED";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			_type = "PORTABILITY";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			_type = "PERFORMANCE";
			break;

		case GL_DEBUG_TYPE_OTHER:
			_type = "OTHER";
			break;

		case GL_DEBUG_TYPE_MARKER:
			_type = "MARKER";
			break;

		default:
			_type = "UNKNOWN";
			break;
		}

		
		switch (Severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			_severity = "ERROR";
			break;

		case GL_DEBUG_SEVERITY_LOW:
		case GL_DEBUG_SEVERITY_MEDIUM:
			_severity = "WARN";
			break;

		default:
			_severity = "INFO";
		}
		

		Log("OpenGL Error " + std::to_string(ID) + " [" + _source + "]: " + std::string(Message), _severity, "OpenGL");
	}

}