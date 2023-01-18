#include "CorePCH.h"
#include "CoreAssert.h"

#include "Logger/Logger.h"
#include "Debug/DebugHelper.h"

void Assertion::OnCheckFailed(const std::wstring& expr, const std::wstring& fileName, const uint32 line, const std::wstring& message)
{
	std::wstring stringFormat;
	std::wstring reason;
	if (message.length() > 0)
	{
		stringFormat = TEXT("Assertion failed: {} [{}] [Line: {}]\n{}\n");
		reason = fmt::format(stringFormat, expr, fileName, line, message);
	}
	else
	{
		stringFormat = TEXT("Assertion failed: {} [{}] [Line: {}]\n");
		reason = fmt::format(stringFormat, expr, fileName, line);
	}
	
	std::wstringstream wss;
	DebugHelper::BuildFailMessage(reason, wss);


}

void Assertion::OnVerifyHResultFailed(const HRESULT hr, const std::wstring& fileName, const uint32 line, const std::wstring& message)
{
	std::wstring stringFormat;
	std::wstring reason;
	if (message.length() > 0)
	{
		stringFormat = TEXT("Verifying HRESULT failed: 0x{:08X} [{}] [Line: {}]\n{}\n");
		reason = fmt::format(stringFormat, hr, fileName, line, message);
	}
	else
	{
		stringFormat = TEXT("Assertion failed: 0x{:08X} [{}] [Line: {}]\n");
		reason = fmt::format(stringFormat, hr, fileName, line);
	}

	reason += TEXT("\nCommon HRESULT Values: https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values\n");

	std::wstringstream wss;
	DebugHelper::BuildFailMessage(reason, wss);


}
