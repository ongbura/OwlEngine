#pragma once

#include "CoreDLL.h"
#include "spdlog/spdlog.h"
#include "Misc/Paths.h"

#define MAX_LOG_LENGTH (512)

enum class ELogLevel : uint8
{
    Trace = spdlog::level::trace,
    Debug = spdlog::level::debug,
    Info = spdlog::level::info,
    Warn = spdlog::level::warn,
    Error = spdlog::level::err,
    Fatal = spdlog::level::critical
};

class CORE_API Logger final
{
public:
	Logger() = delete;
	~Logger() = delete;

	static void Initialize();

    static Path Deinitialize(bool bAborted);

    static void ActivateConsoleLogging();

    static void DeactivateConsoleLogging();
	
    static void SetFilePattern(const char* pattern);

    static void SetConsolePattern(const char* pattern);

    static void SetLevel(ELogLevel level);

    static ELogLevel GetLevel();

	static void Log(ELogLevel level, std::wstringstream& stream);

	template <typename... TArgs>
	static void Log(ELogLevel level, spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Trace(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Debug(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Info(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Warn(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Error(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Fatal(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args);

private:
	static std::wstring getNowTimeString();

	inline static bool mbInitialized = false;
};

template <typename ... TArgs>
void Logger::Log(const ELogLevel level, spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
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
void Logger::Trace(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_TRACE(fmt, args...);
}

template <typename ... TArgs>
void Logger::Debug(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_DEBUG(fmt, args...);
}

template <typename ... TArgs>
void Logger::Info(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_INFO(fmt, args...);
}

template <typename ... TArgs>
void Logger::Warn(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_WARN(fmt, args...);
}

template <typename ... TArgs>
void Logger::Error(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_ERROR(fmt, args...);
}

template <typename ... TArgs>
void Logger::Fatal(spdlog::wformat_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_CRITICAL(fmt, args...);
}
