#pragma once

#include "CoreDLL.h"

class CORE_API Paths
{
public:
	static std::wstring GetEngineDir();

	static std::wstring GetLogDir();

	static std::wstring GetEngineContentDir();

	static std::wstring GetUserContentDir();

	static std::wstring GetConfigDir();
};

