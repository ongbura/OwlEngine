#include "CorePCH.h"
#include "Logger/ScopedLogLevel.h"

ScopedLogLevel::ScopedLogLevel(const ELogLevel level)
	: mCached(Logger::GetLevel())
{
	Logger::SetLevel(level);
}

ScopedLogLevel::~ScopedLogLevel()
{
	Logger::SetLevel(mCached);
}
