#include "CorePCH.h"
#include "Platform/Windows/ProcessPipe.h"

ProcessPipe::ProcessPipe(const bool bSender, const bool bInherit)
	: mbSender(bSender)
	, mbInherit(bInherit)
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = bInherit;
	sa.lpSecurityDescriptor = nullptr;

	if (!CreatePipe(&mReadHandle, &mWriteHandle, &sa, 0))
	{
		// Error Code: https://learn.microsoft.com/ko-kr/windows/win32/debug/system-error-codes
		verifyMsg(false, TEXT("Failed to create pipe. Error Code: {}"), GetLastError());
	}
}

ProcessPipe::~ProcessPipe()
{
	CloseHandle(mReadHandle);
	CloseHandle(mWriteHandle);
}
