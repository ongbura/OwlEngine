#include "CorePCH.h"
#include <format>

#include "StackWalker.h"

#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

bool StackWalker::Walk(std::wstringstream& outStream, const uint32 framesToSkip)
{
	SymInitialize(GetCurrentProcess(), nullptr, TRUE);
	SymSetOptions(SYMOPT_LOAD_LINES);

	const HANDLE process = GetCurrentProcess();
	SymInitializeW(process, nullptr, TRUE);

	void* stackFrames[MAX_STACK_FRAME];
	const WORD stackFrameNum = CaptureStackBackTrace(framesToSkip, MAX_STACK_FRAME, stackFrames, nullptr);

	SYMBOL_INFOW* symbol = static_cast<SYMBOL_INFOW*>(calloc(1, sizeof(SYMBOL_INFOW) + MAX_SYM_NAME * sizeof(TCHAR)));

	if (symbol == nullptr)
	{
		FatalAppExit(0, TEXT("No more memory space to trace call stack."));

		return false;
	}

	symbol->MaxNameLen = MAX_SYM_NAME;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	for (int i = 2; i < stackFrameNum; ++i)
	{
		DWORD64 symbolDisplacement = 0;
		DWORD lineDisplacement = 0;

		if (SymFromAddrW(process, reinterpret_cast<DWORD64>(stackFrames[i]), &symbolDisplacement, symbol))
		{
			IMAGEHLP_MODULEW64 moduleInfo{};
			moduleInfo.SizeOfStruct = sizeof(moduleInfo);

			IMAGEHLP_LINEW64 lineInfo{};
			lineInfo.SizeOfStruct = sizeof(lineInfo);

			if (SymGetModuleInfoW64(process, symbol->ModBase, &moduleInfo) && SymGetLineFromAddrW64(
				process, reinterpret_cast<DWORD64>(stackFrames[i]), &lineDisplacement, &lineInfo))
			{
				if (wcsstr(symbol->Name, TEXT("__scrt")))
				{
					continue;
				}

				const auto moduleName = getModuleName(reinterpret_cast<LPCWSTR>(symbol->Address));

				outStream << std::format(
					TEXT("0x{:08X} {}!{}() [{}:{}]\n"), symbol->Address, moduleName, symbol->Name, lineInfo.FileName,
					lineInfo.LineNumber);
			}
		}
	}

	return true;
}

std::wstring StackWalker::getModuleName(LPCWSTR symbolAddress)
{
	TCHAR path[1024];
	HMODULE hm = nullptr;

	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
	                  GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
	                  symbolAddress, &hm);

	if (const DWORD length = GetModuleFileName(hm, path, 1024); length > 0)
	{
		TCHAR* p = path + length - 1;

		while (true)
		{
			if (*(p - 1) == TEXT('\\'))
			{
				break;
			}

			p--;
		}

		return { p };
	}

	return { path };
}
