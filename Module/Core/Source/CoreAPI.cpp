#include "CorePCH.h"
#include "CoreAPI.h"

#include "Debug/DebugHelper.h"

void InitializeCoreApi()
{
	static bool bInitialized = false;

	if (bInitialized)
	{
		return;
	}

	// Set unhandled exception filter function.
	SetUnhandledExceptionFilter(DebugHelper::ExceptionFilter);

	// Initialize Logger
	Logger::Initialize();

	// TODO: Initialize Config

	bInitialized = true;
}
