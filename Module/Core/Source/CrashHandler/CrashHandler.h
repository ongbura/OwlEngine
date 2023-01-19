#pragma once

#include "Misc/Paths.h"

class CrashHandler
{
public:
	static LONG __stdcall ExceptionFilter(EXCEPTION_POINTERS* exceptionPointers);

	static void HandleCrash(const std::vector<std::wstring>& details);

private:
	static void logDebugMessage(const std::vector<std::wstring>& details);

	static void forceTerminate();

	static void executeCrashReporter(const Path& logFilePath, const std::wstring& debugMessage, const Path& enginePath);

	static std::wstring exceptionCodeToString(DWORD code);

	inline static std::wstringstream mDebugMessageHeader{};
	inline static std::wstringstream mDebugMessageBody{};
};
