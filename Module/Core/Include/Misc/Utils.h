#pragma once

class Utils
{
public:
	static std::wstring StringToWideString(const std::string& str);

	static std::string WideStringToString(const std::wstring& str);
};

