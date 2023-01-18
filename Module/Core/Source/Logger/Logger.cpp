#include "CorePCH.h"
#include "Logger/Logger.h"

#include "Misc/Paths.h"

#pragma warning( disable : 4819 26450 26451 26437 4804 26498 26800 26812 26498 26495 4806 6285 )

#include "spdlog/sinks/ostream_sink.h"
#pragma warning( default : 4819 26450 26451 26437 4804 26498 26800 26812 26498 26495 4806 6285 )

void Logger::Initialize()
{
	std::vector<spdlog::sink_ptr> sinks;

	auto lazySink = std::make_shared<spdlog::sinks::ostream_sink_mt>(mLazyStream);
	sinks.emplace_back(lazySink);

	spdlog::set_default_logger(std::make_shared<spdlog::logger>("defaultLogger", begin(sinks), end(sinks)));
	spdlog::set_pattern("[%Y/%m/%d %T] [%l] %!(): %v");
}

void Logger::SetLevel(const ELogLevel level)
{
	spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}

ELogLevel Logger::GetLevel()
{
	return static_cast<ELogLevel>(spdlog::get_level());
}

std::wstring Logger::WriteFile(const std::string additionalMessage)
{
	std::wstring fileName = Paths::GetLogDir();
	fileName += TEXT("OwlEngine-");
	fileName += getCurrentTime();
	fileName += TEXT(".log");
	
	std::ofstream fOut;
	fOut.open(fileName, std::ios_base::out | std::ios_base::binary);

	if (fOut.is_open())
	{
		fOut << mLazyStream.str();
		fOut << additionalMessage;

		fOut.close();
	}

	return fileName;
}

std::wstring Logger::getCurrentTime()
{
	const auto timer = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm tBuff{};
	localtime_s(&tBuff, &timer);  // NOLINT(cert-err33-c)

	std::wstringstream ss;
	ss << std::put_time(&tBuff, TEXT("%Y.%m.%d-%H.%M.%S"));

	return ss.str();
}
