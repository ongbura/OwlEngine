#include "CorePCH.h"
#include "Platform/Windows/WindowsEvent.h"

WindowsEvent::WindowsEvent(const bool bInherit)
{
	static uint32 instanceCount{ 0 };

	mName = std::format(TEXT("Local\\OwlEngine_WindowsEvent{}"), instanceCount);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = bInherit;
	sa.lpSecurityDescriptor = nullptr;

	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventexw
	mHandle = CreateEventEx(&sa, mName.c_str(),
	                        CREATE_EVENT_INITIAL_SET | CREATE_EVENT_MANUAL_RESET,
	                        EVENT_MODIFY_STATE | SYNCHRONIZE);
	
	if (mHandle == nullptr)
	{
		// Error Code: https://learn.microsoft.com/ko-kr/windows/win32/debug/system-error-codes
		verifyMsg(false, TEXT("Failed to create windows event. Error Code: {}"), GetLastError());
	}

	instanceCount++;
	mbSignaled = true;
}

WindowsEvent::~WindowsEvent()
{
	CloseHandle(mHandle);
}

void WindowsEvent::WaitForSignal()
{
	//TODO: 데드락 방지
	const DWORD waitResult = WaitForSingleObject(mHandle, INFINITE);
	verifyMsg(waitResult == WAIT_OBJECT_0, TEXT("Failed to wait signal. Error Code: {}"), GetLastError());

	mbSignaled = true;
}

void WindowsEvent::Reset()
{
	ResetEvent(mHandle);
	mbSignaled = false;
}
