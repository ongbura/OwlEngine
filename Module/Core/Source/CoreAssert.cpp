#include "CorePCH.h"
#include "CoreAssert.h"

#include "CrashHandler/CrashHandler.h"

void Assertion::OnCheckFailed(const std::wstring& expr, const std::wstring& fileName, const uint32 line, const std::wstring& message)
{
	std::vector<std::wstring> details;
	details.emplace_back(std::format(TEXT("Assertion failed: {} [{}] [Line: {}]"), expr, fileName, line));

	if (!message.empty())
	{
		details.push_back(message);
	}

	CrashHandler::HandleCrash(details);
}

void Assertion::OnVerifyHResultFailed(const HRESULT hr, const std::wstring& fileName, const uint32 line, const std::wstring& message)
{
	std::vector<std::wstring> details;
	details.emplace_back(std::format(TEXT("Verifying HRESULT failed: 0x{:08X} [{}] [Line: {}]"), hr, fileName, line));

	if (!message.empty())
	{
		details.push_back(message);
	}

	details.emplace_back(TEXT("\nCommon HRESULT Values: https://learn.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values"));

	CrashHandler::HandleCrash(details);
}
