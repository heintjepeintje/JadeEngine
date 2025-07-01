#include <Jade/Jade.hpp>

#include <cstdlib>

template<> 
struct Jade::Formatter<Jade::Time> { static String FormatType(const Time &value) { return Float64ToString(value.GetSeconds()); } };

int main(int argc, char **argv) {
	Jade::Logger logger("Jade.Editor");

	Jade::Time time(1234);

	logger.Log(Jade::LogLevel::Fatal, "This is a fatal message. Took: {}s", time);
	logger.Log(Jade::LogLevel::Error, "This is an error message");
	logger.Log(Jade::LogLevel::Warning, "This is a warning message");
	logger.Log(Jade::LogLevel::Info, "This is an info message");
	logger.Log(Jade::LogLevel::Debug, "This is a debug message");
	logger.Log(Jade::LogLevel::Trace, "This is a trace message");

	logger.Log(Jade::LogLevel::Info, "Current time: {}", Jade::Time::Now());

	Jade::DebugBreak();

	return 0;
}