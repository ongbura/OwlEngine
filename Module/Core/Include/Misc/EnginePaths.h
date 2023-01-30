#pragma once

#include <filesystem>

#include "CoreDLL.h"

class CORE_API EnginePaths
{
public:
	EnginePaths() = delete;
	~EnginePaths() = delete;
	
	static std::filesystem::path GetLogDir();

	static std::filesystem::path GetEngineContentDir();

	static std::filesystem::path GetUserContentDir();

	static std::filesystem::path GetConfigDir();

	static std::filesystem::path GetWorkingDir();

private:
	static std::filesystem::path getContentDir();
};
