#include "CorePCH.h"
#include "Logger/Logger.h"

#include "Misc/Paths.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/sinks/basic_file_sink.h"

#define FILE_SINK_INDEX (0)
#define CONSOLE_SINK_INDEX (1)
#define CALL_STACK_START ()

static std::wstring gLoggingFilename(MAX_PATH, TEXT('0'));
static constexpr std::string gClosingPattern{ "[[%Y-%m-%d %H:%M:%S.$e]][%l] %v" };

void Logger::Initialize()
{
	gLoggingFilename = std::format(TEXT("{}OwlEngine-Running.log"), Paths::GetLogDir());
	
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(gLoggingFilename, true);
	const auto engineLogger = std::make_shared<spdlog::logger>("EngineLogger", fileSink);
	
	spdlog::set_default_logger(engineLogger);

	// set file sink pattern
	spdlog::default_logger()->sinks()[0]->set_pattern("[%Y-%m-%d %H:%M:%S.$e][%l]%!: %v");
}

void Logger::Deinitialize(const bool bAborted, std::wstringstream& closingMessageStream)
{
	if (spdlog::default_logger()->sinks().size() > CONSOLE_SINK_INDEX)
	{
		DeactivateConsoleLogging();
	}

	spdlog::default_logger()->set_pattern(gClosingPattern);

	if (!bAborted)
	{
		if (closingMessageStream.)
		while (!closingMessageStream.eof())
		{
			std::wstring line;
			line.reserve(MAX_PATH);
			std::getline(closingMessageStream, line);

			spdlog::info(line);
		}


		spdlog::info(TEXT("Closing log file..."));
	}
	else
	{
		bool bHeader = true;
		constexpr std::wstring_view hexPrefix{ TEXT("0x") };

		while (!closingMessageStream.eof())
		{
			std::wstring line;
			line.reserve(MAX_PATH);
			std::getline(closingMessageStream, line);

			if (bHeader)
			{
				// call stack symbol address's prefix is "0x"
				// if line start with "0x", we are not on the header
				const std::wstring_view prefix(line.cbegin(), line.cbegin() + 1);

				if (hexPrefix.compare(prefix) == 0)
				{
					spdlog::default_logger()->set_pattern("[[%Y-%m-%d %H:%M:%S.$e]][%l] [Callstack] %v");
					bHeader = false;
				}
			}

			spdlog::critical(line);
		}

		spdlog::default_logger()->set_pattern(gClosingPattern);
		spdlog::critical(TEXT(""));
		spdlog::critical(TEXT("Closing log file..."));
	}
	
	spdlog::drop_all();
	
	assert(std::filesystem::exists(gLoggingFilename));

	const auto finalLogFilename = std::format(TEXT("{}OwlEngine-{}.log"), Paths::GetLogDir(), getNowTimeString());

	std::filesystem::rename(gLoggingFilename, finalLogFilename);
}

void Logger::ActivateConsoleLogging()
{
	// TODO: implementation
}

void Logger::DeactivateConsoleLogging()
{
	// TODO: implementation
}

void Logger::SetFileLogPattern(const std::string& pattern)
{
	spdlog::default_logger()->sinks()[FILE_SINK_INDEX]->set_pattern(pattern);
}

void Logger::SetConsoleLogPattern(const std::string& pattern)
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

std::wstring Logger::getNowTimeString()
{
	const auto timer = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm tBuff{};
	localtime_s(&tBuff, &timer);  // NOLINT(cert-err33-c)

	std::wstringstream ss;
	ss << std::put_time(&tBuff, TEXT("%Y.%m.%d-%H.%M.%S"));

	return ss.str();
}
