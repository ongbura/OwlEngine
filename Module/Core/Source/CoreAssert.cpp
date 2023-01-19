#include "CorePCH.h"
#include "CoreAssert.h"

#include <shellapi.h>

#include "Logger/Logger.h"
#include "Debug/DebugHelper.h"

void Assertion::OnCheckFailed(const std::wstring& expr, const std::wstring& fileName, const uint32 line, const std::wstring& message)
{
	std::wstring reason;
	if (message.length() > 0)
	{
		reason = std::format(TEXT("Assertion failed: {} [{}] [Line: {}]\n{}\n"), expr, fileName, line, message);
	}
	else
	{
		reason = std::format(TEXT("Assertion failed: {} [{}] [Line: {}]\n"), expr, fileName, line);
	}
	
	std::wstringstream wss;

	DebugHelper::BuildDebugMessage(reason, wss);
	Logger::Deinitialize(true, wss);
	
	// CrashReporter ½ÇÇà ³¡
	ShellExecute(nullptr, TEXT("open"), TEXT(R"("E:\Repositories\OwlEngine\Binaries\Debug\CrashReporter.exe")"), wss.str().c_str(), nullptr, SW_HIDE);
}

void Assertion::OnVerifyHResultFailed(const HRESULT hr, const std::wstring& fileName, const uint32 line, const std::wstring& message)
{
	std::wstring reason;
	if (message.length() > 0)
	{
		reason = std::format(TEXT("Verifying HRESULT failed: 0x{:08X} [{}] [Line: {}]\n{}\n"), hr, fileName, line, message);
	}
	else
	{
		reason = std::format(TEXT("Assertion failed: 0x{:08X} [{}] [Line: {}]\n"), hr, fileName, line);
	}

	reason += TEXT("\nCommon HRESULT Values: https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values \n");

	std::wstringstream wss;
	DebugHelper::BuildDebugMessage(reason, wss);


}
