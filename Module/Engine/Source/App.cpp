#include "EnginePCH.h"
#include "App.h"

INITIATE_WIN32_APPLICATION()

HRESULT App::Run(HINSTANCE hInstance, int nCmdShow)
{
	// const HRESULT hr = initializeApplication(hInstance, nCmdShow);
	// VERIFY_HRESULT(hr);

	// Initialize Core APIs...
	Core::InstallUnhandledExceptionFilter();
	Logger::Initialize();


	CHECK(false);

}

HRESULT App::initializeApplication(HINSTANCE hInstance, int nCmdShow)
{
	return S_OK;
}

void App::terminateApplication()
{
}

LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// case WM_SIZE:
		// {
		// 	const auto mainWindow = gEngine->GetMainWindow();
		// 	check(mainWindow.get());
		//
		// 	const int32 newWidth = LOWORD(lParam);
		// 	const int32 newHeight = LOWORD(lParam);
		//
		// 	if (wParam == SIZE_MINIMIZED)
		// 	{
		// 		sbShouldStop = true;
		// 		mainWindow->SetMinimized(true);
		// 	}
		// 	else if (wParam == SIZE_MAXIMIZED)
		// 	{
		// 		mainWindow->OnResized(newWidth, newHeight);
		// 	}
		// 	else if (wParam == SIZE_RESTORED)
		// 	{
		// 		if (mainWindow->IsMinimized())
		// 		{
		// 			sbShouldStop = false;
		// 			mainWindow->SetMinimized(false);
		// 		}
		//
		// 		mainWindow->OnResized(newWidth, newHeight);
		// 	}
		// }
		// break;
		// case WM_ENTERSIZEMOVE:
		// 	sbShouldStop = true;
		// 	break;
		// case WM_EXITSIZEMOVE:
		// 	sbShouldStop = false;
		// 	break;
			// Check if the window is being destroyed or closed.
	case WM_DESTROY:
		// Intentional fall through...
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
		// All other messages pass to the message handler in the system class.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
