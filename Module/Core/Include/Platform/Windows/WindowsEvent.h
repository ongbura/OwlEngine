#pragma once

#include "CoreDLL.h"

class CORE_API WindowsEvent
{
public:
	explicit WindowsEvent(bool bInherit = true);
	WindowsEvent(const WindowsEvent&) = delete;
	WindowsEvent(WindowsEvent&&) = delete;
	WindowsEvent& operator=(const WindowsEvent&) = delete;
	WindowsEvent& operator=(WindowsEvent&&) = delete;

	~WindowsEvent();

	void WaitForSignal();

	void Reset();

	std::wstring GetName() const { return mName; }
	HANDLE GetHandle() const { return mHandle; }
	bool IsSignaled() const { return mbSignaled; }
	
private:
	std::wstring mName{};
	HANDLE mHandle{ nullptr };
	bool mbSignaled{ false };
};

