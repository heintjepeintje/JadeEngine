#pragma once

#include <Jade/Core/String.hpp>
#include <Jade/System/IO.hpp>
#include <Jade/Core/Format.hpp>

namespace Jade {

	enum class LogLevel {
		None = 0,
		Fatal, Error, Warning,
		Info, Debug, Trace
	};

	class Logger {
	public:
		Logger(const String &name, LogLevel level = LogLevel::Trace) : mName(name), mLevel(level) { }
		~Logger() { }

		inline void SetLevel(LogLevel level) { mLevel = level; }
		inline LogLevel GetLevel() const { return mLevel; }

		template<typename ..._Args>
		inline void Log(LogLevel level, const String &format, _Args &&...args) {
			if (level > mLevel) return;
			String outputMessage;
			switch (level) {
				case LogLevel::Fatal:   outputMessage = GetConsoleColorAsString(ConsoleColor::White, ConsoleColor::Red) + "[" + mName + "] FATAL > "; break;
				case LogLevel::Error:   outputMessage = GetConsoleColorAsString(ConsoleColor::Red) + "[" + mName + "] ERROR > "; break;
				case LogLevel::Warning: outputMessage = GetConsoleColorAsString(ConsoleColor::Yellow) + "[" + mName + "] WARNING > "; break;
				case LogLevel::Info:    outputMessage = GetConsoleColorAsString(ConsoleColor::Blue) + "[" + mName + "] INFO > "; break;
				case LogLevel::Debug:   outputMessage = GetConsoleColorAsString(ConsoleColor::Green) + "[" + mName + "] DEBUG > "; break;
				case LogLevel::Trace:   outputMessage = GetConsoleColorAsString(ConsoleColor::Magenta) + "[" + mName + "] TRACE > "; break;
				default:                return;
			}

			outputMessage += Format(format, Jade::Forward<_Args>(args)...) + GetConsoleColorAsString(ConsoleColor::Normal) + "\n";
			WriteConsole(outputMessage);
		}

		template<typename ..._Args>
		inline void LogTrace(const String &format, _Args &&...args) { Log(LogLevel::Trace, format, Forward<_Args>(args)...); }
		template<typename ..._Args>
		inline void LogDebug(const String &format, _Args &&...args) { Log(LogLevel::Debug, format, Forward<_Args>(args)...); }
		template<typename ..._Args>
		inline void LogInfo(const String &format, _Args &&...args) { Log(LogLevel::Info, format, Forward<_Args>(args)...); }
		template<typename ..._Args>
		inline void LogWarning(const String &format, _Args &&...args) { Log(LogLevel::Warning, format, Forward<_Args>(args)...); }
		template<typename ..._Args>
		inline void LogError(const String &format, _Args &&...args) { Log(LogLevel::Error, format, Forward<_Args>(args)...); }
		template<typename ..._Args>
		inline void LogFatal(const String &format, _Args &&...args) { Log(LogLevel::Fatal, format, Forward<_Args>(args)...); }

		inline void NewLine() { WriteConsole("\n"); }

	private:
		String mName;
		LogLevel mLevel;
	};

}