#include <iostream>
#include <fstream>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
private:
    std::ofstream out;

    const char* logLevelToString(LogLevel logLevel)
    {
        switch (logLevel)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        }

        return "Invalid log level";
    }

public:
    Logger(const char* fileName)
    {
        out.open(fileName);

        if (!out.is_open())
        {
            throw std::runtime_error("Problem while opening the file");
        }
    }

    Logger(const Logger& other) = delete;
    Logger& operator = (const Logger& other) = delete;

    ~Logger()
    {
        out.close();
    }

    void operator () (const char* message, LogLevel logLevel)
    {
        out << '[' << logLevelToString(logLevel) << "]: " << message << '\n';
    }
};

int main ()
{
    Logger logger("logs.txt");

    logger("test info log", LogLevel::INFO);
    logger("test debug log", LogLevel::DEBUG);
    logger("test error log", LogLevel::ERROR);

    return 0;
}