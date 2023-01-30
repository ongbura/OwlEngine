#pragma once

#include "CoreDLL.h"
#include "Misc/EnginePaths.h"

class CrashHandler
{
public:
	static void CORE_API Initialize();

	static LONG __stdcall ExceptionFilter(EXCEPTION_POINTERS* exceptionPointers);

	static void CORE_API HandleCrash(const std::vector<std::wstring>& details);

private:
	static void logDebugMessage(const std::vector<std::wstring>& details);

	static void forceTerminate();

	static void executeCrashReporter(const std::filesystem::path& logFilePath, const std::wstring& debugMessage,
	                                 const std::filesystem::path& enginePath);

	static std::wstring exceptionCodeToString(DWORD code);

	inline static std::wstringstream mDebugMessageHeader{};
	inline static std::wstringstream mDebugMessageBody{};
};
