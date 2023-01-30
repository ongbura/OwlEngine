#pragma once

class App
{
public:
	static HRESULT Run(HINSTANCE hInstance, int nCmdShow);

	static HINSTANCE GetInstanceHandle() { return mInstanceHandle; }

private:
	static HRESULT initializeApplication(HINSTANCE hInstance, int nCmdShow);

	static void terminateApplication();

	inline static bool mbShouldStop = false;

	inline static HINSTANCE mInstanceHandle = nullptr;

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#if defined(_WIN32) || defined(_WIN64)
#define INITIATE_WIN32_APPLICATION() \
	int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /* hPrevInstance */, _In_ LPWSTR /* lpCmdLine */, _In_ int nCmdShow) \
	{ \
		return App::Run(hInstance, nCmdShow); \
	}
#endif
