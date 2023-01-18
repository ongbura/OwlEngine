#pragma once

#include "CoreDLL.h"
#include "Logger.h"

class CORE_API ScopedLogLevel final
{
public:
	explicit ScopedLogLevel(ELogLevel level);
	~ScopedLogLevel();

private:
	ELogLevel mCached;
};

#define SCOPED_LOG_LEVEL(level) ScopedLogLevel sll(level)
