#include "CorePCH.h"
#include "Misc/SystemInfo.h"

#define MAX_PROCESSOR_NAME_LEN (128)

std::wstring SystemInfo::GetProcessorName()
{
	TCHAR ret[MAX_PROCESSOR_NAME_LEN];
	constexpr DWORD retByteSize = sizeof(ret);
	HKEY hKey;

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Hardware\\Description\\System\\CentralProcessor\\0"), 0, KEY_QUERY_VALUE, &hKey);
	RegQueryValueEx(hKey, TEXT("ProcessorNameString"), nullptr, nullptr, reinterpret_cast<LPBYTE>(ret), nullptr);
	RegCloseKey(hKey);


	return { ret };
}

std::wstring SystemInfo::GetOperatingSystemName()
{
	return {};
}
