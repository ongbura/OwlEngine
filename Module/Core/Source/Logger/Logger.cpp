#include "CorePCH.h"
#include "Logger/Logger.h"

#include "Misc/EnginePaths.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

#define FILE_SINK_INDEX (0)
#define CONSOLE_SINK_INDEX (1)
#define CALL_STACK_START ()

static std::filesystem::path gLoggingFilePath{};
static std::wstring gStreamLine{};
static const std::string gPatternWithSymbol{ "[%Y-%m-%d %H:%M:%S.$e][%l]%!: %v" };
static const std::string gPatternWithoutSymbol{ "[[%Y-%m-%d %H:%M:%S.$e]][%l] %v" };

void Logger::Initialize()
{
	assert(!mbInitialized);
	
	gLoggingFilePath = EnginePaths::GetLogDir() / TEXT("OwlEngine-Running.log");

	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(gLoggingFilePath, true);
	const auto engineLogger = std::make_shared<spdlog::logger>("EngineLogger", fileSink);
	
	spdlog::set_default_logger(engineLogger);

	// set file sink pattern
	SetFileLogPattern(gPatternWithSymbol.c_str());

	gStreamLine.reserve(MAX_LOG_LENGTH);

	mbInitialized = true;
}

std::filesystem::path Logger::Deinitialize(const bool bAborted)
{
	assert(mbInitialized);

	if (spdlog::default_logger()->sinks().size() > CONSOLE_SINK_INDEX)
	{
		DeactivateConsoleLogging();
	}

	spdlog::default_logger()->set_pattern(gPatternWithoutSymbol);
	
	const auto level = bAborted ? spdlog::level::level_enum::err : spdlog::level::level_enum::info;
		
	spdlog::log(level, TEXT("Closing log file..."));
	spdlog::drop_all();
	
	assert(std::filesystem::exists(gLoggingFilePath));

	// const auto finalLogFilename = std::format(TEXT("{}OwlEngine-{}.log"), EnginePaths::GetLogDir(), getNowTimeString());
	const auto finalLogFilename = std::format(TEXT("OwlEngine-{}.log"), getNowTimeString());
	const auto finalLogFilePath = EnginePaths::GetLogDir() / finalLogFilename;

	std::filesystem::rename(gLoggingFilePath, finalLogFilePath);

	mbInitialized = false;
	return finalLogFilePath;
}

void Logger::ActivateConsoleLogging()
{
	// TODO: implementation
}

void Logger::DeactivateConsoleLogging()
{
	// TODO: implementation
}

void Logger::SetFileLogPattern(const char* pattern)
{
	assert(spdlog::default_logger()->sinks().size() == 1);
	spdlog::default_logger()->sinks()[FILE_SINK_INDEX]->set_pattern(pattern);
}

void Logger::SetConsoleLogPattern(const char* pattern)
{
	// console sink is not
	if (spdlog::default_logger()->sinks().size() == 1)
	{
		return;
	}

	// TODO: implementation
}

void Logger::SetLevel(const ELogLevel level)
{
	spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}

ELogLevel Logger::GetLevel()
{
	return static_cast<ELogLevel>(spdlog::get_level());
}

void Logger::Log(ELogLevel level, std::wstringstream& stream)
{
	const auto logLevel = static_cast<spdlog::level::level_enum>(level);
	
	while (!stream.eof())
	{
		std::getline(stream, gStreamLine);
		spdlog::log(logLevel, gStreamLine);
	}
}

std::wstring Logger::getNowTimeString()
{
	const auto timer = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm tBuff{};
	localtime_s(&tBuff, &timer);  // NOLINT(cert-err33-c)

	std::wstringstream ss;
	ss << std::put_time(&tBuff, TEXT("%Y.%m.%d-%H.%M.%S"));

	return ss.str();
}
