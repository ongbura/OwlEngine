#pragma once

#include "CoreDLL.h"
#include "ProcessPipe.h"
#include "WindowsEvent.h"

//TODO: 생성자에 ostream을 넣어야 할 거 같아. 그리고 operator<<를 오버라이드 해야함.
//TODO: operator<<는 path랑 string, const wchar_t*로 세개 오버로드.
//TODO: powershell의 인코딩을 utf-8로 설정해서 작업해야 함.
//TODO: 이벤트를 관련 테스트를 해봐야 할 거 같음.
//TODO: 비동기로 생성할 수 있는 함수가 존재 해야함. 모든 동작을 비동기로 처리해야 함.
//TODO: 이건 복사 막아야 함
//TODO: ChildProcess 클래스 만들기.
class CORE_API PowerShell
{
public:
	PowerShell();
	PowerShell(const PowerShell&) = delete;
	PowerShell(PowerShell&&) = delete;
	PowerShell& operator=(const PowerShell&) = delete;
	PowerShell& operator=(PowerShell&&) = delete;

	~PowerShell();

	void ExecuteCommand(const std::wstring& command);

	void ExecuteScript() const;

private:
	void readOutputStream() const;

	void writeInputStream(const std::wstring& command);

	HANDLE mProcessHandle{ nullptr };
	DWORD mProcessId{ 0 };

	HANDLE mThreadHandle{ nullptr };
	DWORD mThreadId{ 0 };
	
	ProcessPipe mSendingPipe;
	ProcessPipe mReceivingPipe;
	WindowsEvent mNotifyEvent;
};
