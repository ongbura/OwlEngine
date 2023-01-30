#pragma once

#include <intrin.h>
#include "CoreDLL.h"
#include "CrashHandler/CrashHandler.h"

class CORE_API Assertion
{
public:
	static void OnCheckFailed(const WCHAR* expr, const WCHAR* fileName, const uint32 line, const std::wstring& message)
	{
		std::vector<std::wstring> details;
		details.emplace_back(std::format(TEXT("Assertion failed: {} [{}] [Line: {}]"), expr, fileName, line));

		if (!message.empty())
		{
			details.push_back(message);
		}

		CrashHandler::HandleCrash(details);
	}

	static void OnVerifyHResultFailed(const HRESULT hr, const WCHAR* fileName, const uint32 line, const std::wstring& message)
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

	static void OnVerifyFailed(const WCHAR* expr, const WCHAR* fileName, const uint32 line, const std::wstring& message)
	{
		std::vector<std::wstring> details;
		details.emplace_back(std::format(TEXT("Verifying failed: {} [{}] [Line: {}]"), expr, fileName, line));

		if (!message.empty())
		{
			details.push_back(message);
		}

		CrashHandler::HandleCrash(details);
	}
};

#define DEBUG_BREAK() (__nop(), __debugbreak())
#define CAT(first, second) first##second
#define WIDE_LITERAL(expr) CAT(L, #expr)

#define CHECK_MSG_IMPL(expr, format_string, ...) \
		do \
		{ \
			if (!(expr)) \
			{ \
				DEBUG_BREAK(); \
				Assertion::OnCheckFailed(WIDE_LITERAL(expr), TEXT(__FILE__), __LINE__, std::format(format_string, ##__VA_ARGS__)); \
			} \
		} while (false)

#define CHECK_IMPL(expr) CHECK_MSG_IMPL(expr, TEXT(""))

#ifdef _DEBUG
#define check(expr) CHECK_IMPL(expr)
#define checkMsg(expr, format_string, ...) CHECK_MSG_IMPL(expr, format_string, ##__VA_ARGS__)
#else
#define check(expr) (void(0))
#define checkMsg(expr, format, ...) (void(0))
#endif

#define VERIFY_HRESULT_MSG_IMPL(result, ...) \
		do \
		{ \
			if (FAILED(result)) \
			{ \
				DEBUG_BREAK(); \
				Assertion::OnVerifyHResultFailed(result, TEXT(__FILE__), __LINE__,  std::format(##__VA_ARGS__)); \
			} \
		} while (false)

#define verifyHResult(result, ...) VERIFY_HRESULT_MSG_IMPL(result, ##__VA_ARGS__)

#define VERIFY_MSG_IMPL(expr, format_string, ...) \
		do \
		{ \
			if (!(expr)) \
			{ \
				DEBUG_BREAK(); \
				Assertion::OnVerifyFailed(WIDE_LITERAL(expr), TEXT(__FILE__), __LINE__, std::format(format_string, ##__VA_ARGS__)); \
			} \
		} while (false)

#define VERIFY_IMPL(expr) VERIFY_MSG_IMPL(expr, TEXT(""))

#define verify(expr) VERIFY_IMPL(expr)
#define verifyMsg(expr, format_string, ...) VERIFY_MSG_IMPL(expr, format_string, ##__VA_ARGS__)
