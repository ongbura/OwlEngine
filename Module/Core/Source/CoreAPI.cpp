#include "CorePCH.h"
#include "CoreAPI.h"

#include "CrashHandler/CrashHandler.h"

void Core::InstallUnhandledExceptionFilter()
{
	static bool bInitialized = false;

	if (bInitialized)
	{
		return;
	}

	// Set unhandled exception filter function.
	SetUnhandledExceptionFilter(CrashHandler::ExceptionFilter);

	bInitialized = true;
}
