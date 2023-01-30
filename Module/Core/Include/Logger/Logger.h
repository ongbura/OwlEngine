#pragma once

#include "CoreDLL.h"
#include "Misc/EnginePaths.h"

#define MAX_LOG_LENGTH (512)

enum class ELogLevel : uint8
{
	Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

class CORE_API Logger final
{
public:
	Logger() = delete;
	~Logger() = delete;

	static void Initialize();

    static std::filesystem::path Deinitialize(bool bAborted);

    static void ActivateConsoleLogging();

    static void DeactivateConsoleLogging();
	
    static void SetFileLogPattern(const char* pattern);

    static void SetConsoleLogPattern(const char* pattern);

    static void SetLevel(ELogLevel level);

    static ELogLevel GetLevel();

	static void Log(ELogLevel level, std::wstringstream& stream);

	template <typename... TArgs>
	static void Log(ELogLevel level, const std::wstring_view&& fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Trace(const std::wstring_view&& fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Debug(const std::wstring_view&& fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Info(const std::wstring_view&& fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Warn(const std::wstring_view&& fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Error(const std::wstring_view&& fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Fatal(const std::wstring_view&& fmt, TArgs&&... args);

private:
	static std::wstring getNowTimeString();

	inline static bool mbInitialized = false;
};

template <typename ... TArgs>
void Logger::Log(const ELogLevel level, const std::wstring_view&& fmt, TArgs&&... args)
{
	switch (level)
	{
	case ELogLevel::Trace:
		SPDLOG_TRACE(fmt, args...);
		break;
	case ELogLevel::Debug:
		SPDLOG_DEBUG(fmt, args...);
		break;
	case ELogLevel::Info:
		SPDLOG_INFO(fmt, args...);
		break;
	case ELogLevel::Warn:
		SPDLOG_WARN(fmt, args...);
		break;
	case ELogLevel::Error:
		SPDLOG_ERROR(fmt, args...);
		break;
	case ELogLevel::Fatal:
		SPDLOG_CRITICAL(fmt, args...);
		break;
	default:
		assert(false);
	}
}

template <typename ... TArgs>
void Logger::Trace(const std::wstring_view&& fmt, TArgs&&... args)
{
    SPDLOG_TRACE(fmt, args...);
}

template <typename ... TArgs>
void Logger::Debug(const std::wstring_view&& fmt, TArgs&&... args)
{
    SPDLOG_DEBUG(fmt, args...);
}

template <typename ... TArgs>
void Logger::Info(const std::wstring_view&& fmt, TArgs&&... args)
{
    SPDLOG_INFO(fmt, args...);
}

template <typename ... TArgs>
void Logger::Warn(const std::wstring_view&& fmt, TArgs&&... args)
{
    SPDLOG_WARN(fmt, args...);
}

template <typename ... TArgs>
void Logger::Error(const std::wstring_view&& fmt, TArgs&&... args)
{
    SPDLOG_ERROR(fmt, args...);
}

template <typename ... TArgs>
void Logger::Fatal(const std::wstring_view&& fmt, TArgs&&... args)
{
    SPDLOG_CRITICAL(fmt, args...);
}
