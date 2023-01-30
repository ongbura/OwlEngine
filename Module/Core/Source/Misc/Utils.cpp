#include "CorePCH.h"
#include "Misc/Utils.h"


std::wstring Utils::StringToWideString(const std::string& str)
{
	if (str.length() == 0)
	{
		return {};
	}

	std::wstring ret;
	const uint32 len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), nullptr, 0);
	CHECK_MSG(len > 0, TEXT("MultiByteToWideChar Failed. ErrorCode = {}"), GetLastError());
	// https://learn.microsoft.com/ko-kr/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar

	ret.resize(len);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), ret.data(), len);

	return ret;
}

std::string Utils::WideStringToString(const std::wstring& str)
{
	if (str.length() == 0)
	{
		return {};
	}

	std::string ret;
	const uint32 len = WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.length(), nullptr, 0, nullptr, nullptr);
	CHECK_MSG(len > 0, TEXT("WideCharToMultiByte Failed. ErrorCode = {}"), GetLastError());

	ret.resize(len);
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), str.length(), ret.data(), len, nullptr, nullptr);

	return ret;
}
