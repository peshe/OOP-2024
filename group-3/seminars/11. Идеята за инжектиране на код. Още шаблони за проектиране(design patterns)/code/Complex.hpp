//#ifndef __COMPLEX_LOGGER_HEADER__
//#define __COMPLEX_LOGGER_HEADER__
//
//
//class ComplexLogger : public  FileLogger, public  ConsoleLogger {
//public:
//	ComplexLogger(bool addTimestamp = false,
//		LogColor logColor = LogColor::Default,
//		LogErrorColor errorColor = LogErrorColor::Default) :
//		ConsoleLogger(addTimestamp, logColor, errorColor), FileLogger(addTimestamp)
//	{
//	}
//
//	void Log(const std::string& message) const override {
//		FileLogger::Log(message);
//		ConsoleLogger::Log(message);
//	}
//
//	void LogError(const std::string& message) const override {
//		FileLogger::LogError(message);
//		ConsoleLogger::LogError(message);
//	}
//
//	ILogger* clone() const override {
//		return new ComplexLogger(*this);
//	}
//};
//
//#endif