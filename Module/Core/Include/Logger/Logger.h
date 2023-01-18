#pragma once

#include "CoreDLL.h"

#pragma warning( disable : 4819 26450 26451 26437 4804 26498 26800 26812 26498 26495 4806 6285 )
#include "spdlog/spdlog.h"
#pragma warning( default : 4819 26450 26451 26437 4804 26498 26800 26812 26498 26495 4806 6285 )

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

    static void SetLevel(ELogLevel level);

    static ELogLevel GetLevel();

    static std::wstring WriteFile(std::string additionalMessage);

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
	static std::wstring getCurrentTime();

	inline static std::stringstream mLazyStream{};
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
