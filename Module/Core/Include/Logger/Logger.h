#pragma once

#include "CoreDLL.h"
#include "spdlog/spdlog.h"

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
	static void Initialize();

    static void Deinitialize(bool bAborted, std::wstringstream& closingMessageStream);

    static void ActivateConsoleLogging();

    static void DeactivateConsoleLogging();

    static void SetFileLogPattern(const std::string& pattern);

    static void SetConsoleLogPattern(const std::string& pattern);

    static void SetLevel(ELogLevel level);

    static ELogLevel GetLevel();

    template <typename... TArgs>
    static void Trace(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Debug(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Info(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Warn(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Error(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args);

    template <typename... TArgs>
    static void Fatal(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args);

private:
	static std::wstring getNowTimeString();
};

template <typename ... TArgs>
void Logger::Trace(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_TRACE(fmt, args...);
}

template <typename ... TArgs>
void Logger::Debug(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_DEBUG(fmt, args...);
}

template <typename ... TArgs>
void Logger::Info(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_INFO(fmt, args...);
}

template <typename ... TArgs>
void Logger::Warn(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_WARN(fmt, args...);
}

template <typename ... TArgs>
void Logger::Error(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_ERROR(fmt, args...);
}

template <typename ... TArgs>
void Logger::Fatal(spdlog::format_string_t<TArgs...> fmt, TArgs&&... args)
{
    SPDLOG_CRITICAL(fmt, args...);
}
