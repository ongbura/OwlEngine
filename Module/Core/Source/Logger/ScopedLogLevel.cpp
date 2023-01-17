#include "CorePCH.h"
#include "ScopedLogLevel.h"

ScopedLogLevel::ScopedLogLevel(const ELogLevel level)
	: mCached(Logger::GetLevel())
{
	Logger::SetLevel(level);
}

ScopedLogLevel::~ScopedLogLevel()
{
	Logger::SetLevel(mCached);
}
