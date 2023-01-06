#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

#include <iostream>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


/// User defined Functions ///

void TransparentWindows(HWND hwnd, int opacity);





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;


	RegisterClass(&wc);

	// Create the window.

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_POPUP,            // Window style

		// Size and position
		500, 200, 640, 480,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	TransparentWindows(hwnd,70);


	// Create a circular region
	HRGN hrgn = CreateEllipticRgn(0, 0, 400, 400);

	// Set the window's region to the circular region
	SetWindowRgn(hwnd, hrgn, TRUE);

	ShowWindow(hwnd, nCmdShow);


	// Run the message loop.

	MSG msg = { };	
	
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:

		MessageBox(hwnd, L"windows ", L"this is the content", MB_OK);
		return 0;
	//case WM_CLOSE:
	//	if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
	//	{
	//		DestroyWindow(hwnd);
	//	}
	//	return 0;

	case WM_DESTROY:
			PostQuitMessage(0);
		return 0;


	case WM_PAINT:
	{
		HBRUSH hBrush = CreateSolidBrush(RGB(100, 100, 100));

		PAINTSTRUCT ps;
		

		HDC hdc = BeginPaint(hwnd, &ps);
		

		FillRect(hdc, &ps.rcPaint, hBrush);
		
		//DrawText(hdc, L"this is the text", 100, &ps.rcPaint, DT_BOTTOM);
		

		//MoveToEx(hdc, 10, 10, NULL);
		//LineTo(hdc, 100, 100);


		EndPaint(hwnd, &ps);
	}
	return 0;
	
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



///		user defined functions		///


void TransparentWindows(HWND hwnd, int opacity)
{
	// Set WS_EX_LAYERED on this window 
	SetWindowLong(hwnd,
		GWL_EXSTYLE,
		GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Make this window 70% alpha
	SetLayeredWindowAttributes(hwnd, 0, (255 * opacity) / 100, LWA_ALPHA);

}