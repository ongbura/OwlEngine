#pragma once

#define MAX_STACK_FRAME (std::numeric_limits<uint8>::max())

class StackWalker
{
public:
	StackWalker() = delete;
	~StackWalker() = delete;

	static bool Walk(std::wstringstream& outStream, uint32 framesToSkip = 0);

private:
	static std::wstring getModuleName(LPCWSTR symbolAddress);
};

