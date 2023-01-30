#include "CorePCH.h"
#include "Misc/EnginePaths.h"

std::filesystem::path EnginePaths::GetLogDir()
{
	return GetWorkingDir().parent_path() / TEXT("Logs");
}

std::filesystem::path EnginePaths::GetEngineContentDir()
{
	return getContentDir() / TEXT("Logs");
}

std::filesystem::path EnginePaths::GetUserContentDir()
{
	return getContentDir() / TEXT("Logs");
}

std::filesystem::path EnginePaths::GetConfigDir()
{
	return GetWorkingDir().parent_path() / TEXT("Config");
}

std::filesystem::path EnginePaths::GetWorkingDir()
{
	static const std::filesystem::path binariesDir = std::filesystem::current_path();
	return binariesDir;
}

std::filesystem::path EnginePaths::getContentDir()
{
	return GetWorkingDir().parent_path() / TEXT("Content");
}
