

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "windows.h"

void TransparentWindows(HWND hwnd, int opacity)
{
	// Set WS_EX_LAYERED on this window 
	SetWindowLong(hwnd,
		GWL_EXSTYLE,
		GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Make this window 70% alpha
	SetLayeredWindowAttributes(hwnd, 0, (255 * opacity) / 100, LWA_ALPHA);

}

void CirculaWindow(HWND hwnd)
{

	TransparentWindows(hwnd, 70);


	// Create a circular region
	HRGN hrgn = CreateEllipticRgn(0, 0, 230, 230);

	// Set the window's region to the circular region
	SetWindowRgn(hwnd, hrgn, TRUE);

	//ShowWindow(hwnd, nCmdShow);
}


int wmain()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	HWND hwnd1 = window.getSystemHandle();

	CirculaWindow(hwnd1);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
/*
#include <windows.h>



void TransparentWindows(HWND hwnd, int opacity)
{
	// Set WS_EX_LAYERED on this window 
	SetWindowLong(hwnd,
		GWL_EXSTYLE,
		GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	// Make this window 70% alpha
	SetLayeredWindowAttributes(hwnd, 0, (255 * opacity) / 100, LWA_ALPHA);

}

int main()
{
	// Register the window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "CircularWindowClass";
	RegisterClassEx(&wc);

	// Create the window
	HWND hwnd = CreateWindowEx(0, "CircularWindowClass", "Circular Window", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200, NULL, NULL, GetModuleHandle(NULL), NULL);

	
	// Create a circular region
	HRGN hrgn = CreateEllipticRgn(0, 0, 200, 200);
	TransparentWindows(hwnd, 70);

	// Set the window's region to the circular region
	SetWindowRgn(hwnd, hrgn, TRUE);

	// Show the window
	ShowWindow(hwnd, SW_SHOW);

	// Main loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
*/