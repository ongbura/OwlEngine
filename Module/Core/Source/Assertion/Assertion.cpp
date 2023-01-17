#include "CorePCH.h"
#include "Assertion.h"

#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

#include "Logger/Logger.h"

std::wstring ExceptionCodeToString(DWORD code);

std::wstring BuildFailMessage(std::string reason);

std::wstring GetModuleName(LPCWSTR symbolAddress);

std::wstring GetCallStack();

int AssertHook(int reportType, char* message, int* returnValue);

LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo);

void Assertion::Initialize()
{
	// Install the assertion hook function
	_CrtSetReportHook(AssertHook);

	// Install the exception handler function
	SetUnhandledExceptionFilter(ExceptionHandler);
}

std::wstring BuildFailMessage()
{

}

std::wstring ExceptionCodeToString(const DWORD code)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record
	std::wstring ret;

	switch (code)
	{
	case EXCEPTION_ACCESS_VIOLATION: ret = L"EXCEPTION_ACCESS_VIOLATION"; break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: ret = L"EXCEPTION_ARRAY_BOUNDS_EXCEEDED"; break;
	case EXCEPTION_BREAKPOINT: ret = L"EXCEPTION_BREAKPOINT"; break;
	case EXCEPTION_DATATYPE_MISALIGNMENT: ret = L"EXCEPTION_DATATYPE_MISALIGNMENT"; break;
	case EXCEPTION_FLT_DENORMAL_OPERAND: ret = L"EXCEPTION_FLT_DENORMAL_OPERAND"; break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: ret = L"EXCEPTION_FLT_DIVIDE_BY_ZERO"; break;
	case EXCEPTION_FLT_INEXACT_RESULT: ret = L"EXCEPTION_FLT_INEXACT_RESULT"; break;
	case EXCEPTION_FLT_INVALID_OPERATION: ret = L"EXCEPTION_FLT_INVALID_OPERATION"; break;
	case EXCEPTION_FLT_OVERFLOW: ret = L"EXCEPTION_FLT_OVERFLOW"; break;
	case EXCEPTION_FLT_STACK_CHECK: ret = L"EXCEPTION_FLT_STACK_CHECK"; break;
	case EXCEPTION_FLT_UNDERFLOW: ret = L"EXCEPTION_FLT_UNDERFLOW"; break;
	case EXCEPTION_ILLEGAL_INSTRUCTION: ret = L"EXCEPTION_ILLEGAL_INSTRUCTION"; break;
	case EXCEPTION_IN_PAGE_ERROR: ret = L"EXCEPTION_IN_PAGE_ERROR"; break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO: ret = L"EXCEPTION_INT_DIVIDE_BY_ZERO"; break;
	case EXCEPTION_INT_OVERFLOW: ret = L"EXCEPTION_INT_OVERFLOW"; break;
	case EXCEPTION_INVALID_DISPOSITION: ret = L"EXCEPTION_INVALID_DISPOSITION"; break;
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: ret = L"EXCEPTION_NONCONTINUABLE_EXCEPTION"; break;
	case EXCEPTION_PRIV_INSTRUCTION: ret = L"EXCEPTION_PRIV_INSTRUCTION"; break;
	case EXCEPTION_SINGLE_STEP: ret = L"EXCEPTION_SINGLE_STEP"; break;
	case EXCEPTION_STACK_OVERFLOW: ret = L"EXCEPTION_STACK_OVERFLOW"; break;
	default: ret = L""; break;
	}

	return ret;
}

std::wstring GetModuleName(const LPCWSTR symbolAddress)
{
	TCHAR path[MAX_PATH];
	HMODULE hm = NULL;

	if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
		GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		symbolAddress, &hm) == 0)
	{
		int ret = GetLastError();
		fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
		// Return or however you want to handle an error.
	}
	if (GetModuleFileName(hm, path, sizeof(path)) == 0)
	{
		int ret = GetLastError();
		fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
		// Return or however you want to handle an error.
	}

	return { path };
}

std::wstring GetCallStack()
{
	std::wstringstream ret;
	ret << TEXT("\n\n\n");

#define CALL_STACK(expr) ret << TEXT("[CallStack] ") << expr << TEXT("\n");
	
	HANDLE process = GetCurrentProcess();
	SymInitializeW(process, nullptr, TRUE);

	void* stack[128];
	int frames = (int)CaptureStackBackTrace(0, 128, stack, nullptr);

	SYMBOL_INFOW* symbol = (SYMBOL_INFOW*)calloc(1, sizeof(SYMBOL_INFOW) + MAX_SYM_NAME * sizeof(TCHAR));
	symbol->MaxNameLen = MAX_SYM_NAME;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	for (int i = 1; i < frames; ++i)
	{
		DWORD64 displacement = 0;
		DWORD lineDisplacement = 0;

		if (SymFromAddrW(process, (DWORD64)stack[i], &displacement, symbol))
		{
			IMAGEHLP_MODULEW64 moduleInfo;
			memset(&moduleInfo, 0, sizeof(IMAGEHLP_MODULEW64));
			moduleInfo.SizeOfStruct = sizeof(moduleInfo);

			IMAGEHLP_LINEW64 lineInfo;
			memset(&lineInfo, 0, sizeof(IMAGEHLP_LINEW64));
			lineInfo.SizeOfStruct = sizeof(lineInfo);
			
			if (::SymGetModuleInfoW64(process, symbol->ModBase, &moduleInfo) && ::SymGetLineFromAddrW64(process, symbol->Address, &lineDisplacement, &lineInfo))
			{
				if (TCHAR* pFileName = wcsstr(lineInfo.FileName, SOLUTION_DIR))
				{
					
					pFileName += wcslen(SOLUTION_DIR);
					
					std::wstringstream ss;
					ss << "0x" << std::hex << std::uppercase << symbol->Address << " ";
					ss << "ModuleName.dll" << "!";
					ss << symbol->Name << "() ";

					ss << "[" << pFileName << ":";
					ss << std::dec << lineInfo.LineNumber << "] ";

					CALL_STACK(ss.str());
				}
			}
		}
	}

	return ret.str();
}

int AssertHook(int reportType, char* message, int* returnValue)
{
	// Build Fail Message
	// 1. Assert Failed Message
	// 2. CallStack

	// Request Logger Write File (Pass fail message)
	// execute CrashReporter LogFilePath, Fail Message, Engine Binary Path.
	// terminate Program

	exit(1);
}

LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* exceptionInfo)
{
	const auto record = exceptionInfo->ExceptionRecord;
	const auto code = record->ExceptionCode;


	exit(1);
}