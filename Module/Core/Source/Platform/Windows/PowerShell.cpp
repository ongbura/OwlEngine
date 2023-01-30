#include "CorePCH.h"
#include "Platform/Windows/PowerShell.h"
#include "CoreAssertion.h"

#define MAX_OUTPUT_LENGTH (4096)

PowerShell::PowerShell()
	: mSendingPipe(true)
	, mReceivingPipe(false)
	, mNotifyEvent()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.hStdError = mReceivingPipe.GetWriteHandle();
	si.hStdOutput = mReceivingPipe.GetWriteHandle();
	si.hStdInput = mSendingPipe.GetReadHandle();
	si.dwFlags |= STARTF_USESTDHANDLES;

	std::wstring fullCommand(TEXT("powershell.exe"));
	const auto bSuccess = CreateProcess(nullptr, fullCommand.data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi);
	verifyMsg(bSuccess == TRUE, TEXT("Failed to Create PowerShell. Error Code: {}"), GetLastError());

	mProcessHandle = pi.hProcess;
	mProcessId = pi.dwProcessId;
	mThreadHandle = pi.hThread;
	mThreadId = pi.dwThreadId;

	//TODO: print logo message or discard it.
	//TODO: encoding to unicode -> $OutputEncoding = [System.Text.Encoding]::Unicode
}

PowerShell::~PowerShell()
{
	CloseHandle(mProcessHandle);
	CloseHandle(mThreadHandle);
}

void PowerShell::ExecuteCommand(const std::wstring& command)
{
	// if (mbBlocked == true)
	// {
	// 	return;
	// }
	//
	// mbBlocked = true;
	//
	// writeInputStream(command);
	// DWORD waitResult = WaitForSingleObject(mNotifyEventHandle, INFINITE);
	// if (waitResult != WAIT_OBJECT_0)
	// {
	// 	//TODO: GetLastError()로 실패로그 띄우고 종료
	// }
	//
	// readOutputStream();
	//
	//
	// mbBlocked = false;
}

void PowerShell::ExecuteScript() const
{
}

void PowerShell::readOutputStream() const
{

}

void PowerShell::writeInputStream(const std::wstring& command)
{
}
