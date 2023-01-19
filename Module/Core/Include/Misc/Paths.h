#pragma once

#include "CoreDLL.h"

using Path = std::filesystem::path;

class CORE_API Paths
{
public:
	Paths() = delete;
	~Paths() = delete;
	
	static Path GetLogDir();

	static Path GetEngineContentDir();

	static Path GetUserContentDir();

	static Path GetConfigDir();

	static Path GetBinariesDir();

	template <typename... TArgs>
	static Path Combine(TArgs&&... args);

private:
	static Path getContentDir();
};

template <typename ... TArgs>
Path Paths::Combine(TArgs&&... args)
{

}

