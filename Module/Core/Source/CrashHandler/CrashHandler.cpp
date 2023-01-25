#include "CorePCH.h"
#include "CrashHandler.h"

#include <shellapi.h>

#include "StackWalker.h"
#include "Logger/Logger.h"

LONG CrashHandler::ExceptionFilter(EXCEPTION_POINTERS* exceptionPointers)
{
	// disable displaying an application Error message box
	SetErrorMode(SEM_NOGPFAULTERRORBOX);

	const auto exceptionCode = exceptionPointers->ExceptionRecord->ExceptionCode;
	const auto codeString = std::format(TEXT("Unhandled Exception: {}"), exceptionCodeToString(exceptionCode));

	std::vector<std::wstring> details;
	details.emplace_back(codeString);
	details.emplace_back(TEXT("MSDN Exception Code List: https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record"));

	HandleCrash(details);

	/*
	 * EXCEPTION_CONTINUE_SEARCH 0x0
	 * The process is being debugged, so the exception should be passed (as second chance) to the application's debugger.
	 */

	 /*
	  * EXCEPTION_EXECUTE_HANDLER 0x1
	  * If the SEM_NOGPFAULTERRORBOX flag was specified in a previous call to SetErrorMode,
	  * no Application Error message box is displayed.
	  * The function returns control to the exception handler, which is free to take any appropriate action.
	  */
	return EXCEPTION_EXECUTE_HANDLER;
}

void CrashHandler::HandleCrash(const std::vector<std::wstring>& details)
{
	logDebugMessage(details);
	forceTerminate();
}

void CrashHandler::logDebugMessage(const std::vector<std::wstring>& details)
{
	mDebugMessageHeader << TEXT("=== Fatal Error Occurred! ===\n");
	mDebugMessageHeader << TEXT('\n');

	for (uint8 i = 0; i < details.size(); ++i)
	{
		mDebugMessageHeader << details[i] << TEXT('\n');
	}

	mDebugMessageHeader << TEXT('\n');

	Logger::SetFilePattern("[[%Y-%m-%d %H:%M:%S.$e]][%l] %v");
	Logger::Log(ELogLevel::Error, mDebugMessageHeader);

	StackWalker::Walk(mDebugMessageBody);

	Logger::SetFilePattern("[[%Y-%m-%d %H:%M:%S.$e]][%l] [Callstack] %v");
	Logger::Log(ELogLevel::Error, mDebugMessageBody);
}

void CrashHandler::forceTerminate()
{
	const auto logFilename = Logger::Deinitialize(true);

	std::wstringstream debugMessageStream;
	{
		debugMessageStream << TEXT('\"');
		debugMessageStream << mDebugMessageHeader.rdbuf();

		auto* bodyBuffer = mDebugMessageBody.rdbuf();

		while (bodyBuffer->sgetc() != std::wstreambuf::traits_type::eof())
		{
			mDebugMessageBody.ignore(19);

			wchar_t ch;

			do
			{
				ch = bodyBuffer->sbumpc();
				debugMessageStream << ch;
			} while (ch != TEXT('\n'));
		}
		debugMessageStream << TEXT('\"');
	}	

	const auto enginePath = Paths::GetBinariesDir() / TEXT("OwlEngine.exe");
	executeCrashReporter(logFilename, debugMessageStream.str(), enginePath);

	exit(EXIT_FAILURE);
}

void CrashHandler::executeCrashReporter(const Path& logFilePath, const std::wstring& debugMessage,	const Path& enginePath)
{
	const auto arguments = std::format(TEXT("{} {} {}"), logFilePath.wstring(), debugMessage, enginePath.wstring());
	const auto crashReporterPath = Paths::GetBinariesDir() / TEXT("CrashReporter.exe");

	ShellExecute(nullptr, TEXT("open"), crashReporterPath.c_str(), arguments.c_str(), nullptr, SW_HIDE);
}

std::wstring CrashHandler::exceptionCodeToString(const DWORD code)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-exception_record

	switch (code)
	{
	case EXCEPTION_ACCESS_VIOLATION: return { TEXT("EXCEPTION_ACCESS_VIOLATION") };
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return { TEXT("EXCEPTION_ARRAY_BOUNDS_EXCEEDED") };
	case EXCEPTION_BREAKPOINT: return { TEXT("EXCEPTION_BREAKPOINT") };
	case EXCEPTION_DATATYPE_MISALIGNMENT: return { TEXT("EXCEPTION_DATATYPE_MISALIGNMENT") };
	case EXCEPTION_FLT_DENORMAL_OPERAND: return { TEXT("EXCEPTION_FLT_DENORMAL_OPERAND") };
	case EXCEPTION_FLT_DIVIDE_BY_ZERO: return { TEXT("EXCEPTION_FLT_DIVIDE_BY_ZERO") };
	case EXCEPTION_FLT_INEXACT_RESULT: return { TEXT("EXCEPTION_FLT_INEXACT_RESULT") };
	case EXCEPTION_FLT_INVALID_OPERATION: return { TEXT("EXCEPTION_FLT_INVALID_OPERATION") };
	case EXCEPTION_FLT_OVERFLOW: return { TEXT("EXCEPTION_FLT_OVERFLOW") };
	case EXCEPTION_FLT_STACK_CHECK: return { TEXT("EXCEPTION_FLT_STACK_CHECK") };
	case EXCEPTION_FLT_UNDERFLOW: return { TEXT("EXCEPTION_FLT_UNDERFLOW") };
	case EXCEPTION_ILLEGAL_INSTRUCTION: return { TEXT("EXCEPTION_ILLEGAL_INSTRUCTION") };
	case EXCEPTION_IN_PAGE_ERROR: return { TEXT("EXCEPTION_IN_PAGE_ERROR") };
	case EXCEPTION_INT_DIVIDE_BY_ZERO: return { TEXT("EXCEPTION_INT_DIVIDE_BY_ZERO") };
	case EXCEPTION_INT_OVERFLOW: return { TEXT("EXCEPTION_INT_OVERFLOW") };
	case EXCEPTION_INVALID_DISPOSITION: return { TEXT("EXCEPTION_INVALID_DISPOSITION") };
	case EXCEPTION_NONCONTINUABLE_EXCEPTION: return { TEXT("EXCEPTION_NONCONTINUABLE_EXCEPTION") };
	case EXCEPTION_PRIV_INSTRUCTION: return { TEXT("EXCEPTION_PRIV_INSTRUCTION") };
	case EXCEPTION_SINGLE_STEP: return { TEXT("EXCEPTION_SINGLE_STEP") };
	case EXCEPTION_STACK_OVERFLOW: return { TEXT("EXCEPTION_STACK_OVERFLOW") };
	default:
		FatalAppExit(0, TEXT("Can't parse exception code."));
	}

	return {};
}
