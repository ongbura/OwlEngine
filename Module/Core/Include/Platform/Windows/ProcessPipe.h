#pragma once

#include "CoreDLL.h"

class CORE_API ProcessPipe
{
public:
	explicit ProcessPipe(bool bSender, bool bInherit = true);
	ProcessPipe(const ProcessPipe&) = delete;
	ProcessPipe(ProcessPipe&&) = delete;
	ProcessPipe& operator=(const ProcessPipe&) = delete;
	ProcessPipe& operator=(ProcessPipe&&) = delete;

	~ProcessPipe();

	HANDLE GetReadHandle() const { return mReadHandle; }
	HANDLE GetWriteHandle() const { return mWriteHandle; }
	bool IsSender() const { return mbSender; }
	bool IsInherit() const { return mbInherit; }

private:
	bool mbSender;
	bool mbInherit;
	HANDLE mReadHandle{ nullptr };
	HANDLE mWriteHandle{ nullptr };
};
