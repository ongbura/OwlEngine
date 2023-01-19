#include "CorePCH.h"
#include "CoreAPI.h"

#include "Debug/DebugHelper.h"

void Core::InstallUnhandledExceptionFilter()
{
	static bool bInitialized = false;

	if (bInitialized)
	{
		return;
	}

	// Set unhandled exception filter function.
	SetUnhandledExceptionFilter(DebugHelper::ExceptionFilter);

	bInitialized = true;
}
