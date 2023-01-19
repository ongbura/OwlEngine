#include "CorePCH.h"
#include "Misc/Paths.h"

Path Paths::GetLogDir()
{
	return GetBinariesDir().parent_path() / TEXT("Logs");
}

Path Paths::GetEngineContentDir()
{
	return getContentDir() / TEXT("Logs");
}

Path Paths::GetUserContentDir()
{
	return getContentDir() / TEXT("Logs");
}

Path Paths::GetConfigDir()
{
	return GetBinariesDir().parent_path() / TEXT("Config");
}

Path Paths::GetBinariesDir()
{
	static const Path binariesDir = std::filesystem::current_path();
	return binariesDir;
}

Path Paths::getContentDir()
{
	return GetBinariesDir().parent_path() / TEXT("Content");
}
