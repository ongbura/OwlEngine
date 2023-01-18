#include "CorePCH.h"
#include "Misc/Paths.h"

#define LOG_DIR TEXT(R"(Logs\)")
#define ENGINE_CONTENT_DIR TEXT(R"(Content\Engine\)")
#define USER_CONTENT_DIR TEXT(R"(Content\User\)")
#define CONFIG_DIR TEXT(R"(Config\)")

std::wstring Paths::GetEngineDir()
{
	static std::wstring engineDir = ENGINE_DIR;
	return engineDir;
}

std::wstring Paths::GetLogDir()
{
	return GetEngineDir() + LOG_DIR;
}

std::wstring Paths::GetEngineContentDir()
{
	return GetEngineDir() + ENGINE_CONTENT_DIR;
}

std::wstring Paths::GetUserContentDir()
{
	return GetEngineDir() + USER_CONTENT_DIR;
}

std::wstring Paths::GetConfigDir()
{
	return GetEngineDir() + CONFIG_DIR;
}
