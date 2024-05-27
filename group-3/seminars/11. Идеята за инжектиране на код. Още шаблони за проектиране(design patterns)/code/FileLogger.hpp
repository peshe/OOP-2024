//#ifndef __FILE_LOGGER_HEADER__
//#define __FILE_LOGGER_HEADER__
//
//
//
//
//class FileLogger : public virtual ILogger {
//public:
//	FileLogger(bool addTimestamp = false)
//		: addTimestamp(addTimestamp)
//	{
//
//	}
//
//	ILogger* clone() const override {
//		return new FileLogger(*this);
//	}
//
//	void Log(const std::string& message) const override {
//		std::ofstream out("logs.txt", std::ios::app);
//		if (!out) {
//			return;
//		}
//
//		try {
//			if (addTimestamp) {
//				out << "[inf] " << getCurrentTimestamp() << " : " << message << std::endl;
//			}
//			else {
//				out << "[inf] : " << message << std::endl;
//			}
//		}
//		catch (...) {
//			out.close();
//		}
//
//		out.close();
//	}
//
//	void LogError(const std::string& message) const override {
//		std::ofstream out("logs.txt", std::ios::app);
//		if (!out) {
//			return;
//		}
//
//		try {
//			if (addTimestamp) {
//				out << "[err] " << getCurrentTimestamp() << " : " << message << std::endl;
//			}
//			else {
//				out << "[err] : " << message << std::endl;
//			}
//		}
//		catch (...) {
//			out.close();
//		}
//
//		out.close();
//	}
//private:
//	bool addTimestamp;
//
//	std::string getCurrentTimestamp() const {
//		auto now = std::time(nullptr);
//		auto localTime = *std::localtime(&now);
//
//		std::ostringstream oss;
//		oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
//		return oss.str();
//	}
//};
//
//
//#endif`