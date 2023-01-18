#pragma once

#include "CoreDLL.h"

class CORE_API Assertion
{
public:
	static void OnCheckFailed(const std::wstring& expr, const std::wstring& fileName, uint32 line, const std::wstring& message);

	static void OnVerifyHResultFailed(HRESULT hr, const std::wstring& fileName, uint32 line, const std::wstring& message);
};

#define DEBUG_BREAK() (__nop(), __debugbreak())

#define CHECK_IMPL(expr, format_string, ...) \
		do \
		{ \
			if (!(expr)) \
			{ \
				DEBUG_BREAK(); \
				Assertion::OnCheckFailed(TEXT(#expr), __FILE__, __LINE__, fmt::format(format_string, ##__VA_ARGS__)); \
				std::exit(EXIT_FAILURE); \
			} \
		} while (false)

#ifdef _DEBUG
#define CHECK(expr) CHECK_IMPL(expr, TEXT(""))
#define CHECK_MSG(expr, format_string, ...) CHECK_IMPL(expr, format_string, ##__VA_ARGS__)
#else
#define CHECK(expr) (void(0))
#define CHECK_MSG(expr, format, ...) (void(0))
#endif

#define VERIFY_HRESULT_IMPL(result, format_string, ...) \
		do \
		{ \
			if (FAILED(result)) \
			{ \
				DEBUG_BREAK(); \
				Assertion::OnVerifyHResultFailed(result, __FILE__, __LINE__,  fmt::format(format_string, ##__VA_ARGS__)); \
				std::exit(EXIT_FAILURE); \
			} \
		} while (false)

#define VERIFY_HRESULT(result) VERIFY_HRESULT_IMPL(result, TEXT(""))
#define VERIFY_HRESULT_MSG(result, format_string, ...) VERIFY_HRESULT_IMPL(result, format_string, ##__VA_ARGS__)
