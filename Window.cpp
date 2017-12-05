#include "Window.h"
#include <stdexcept>

Window::Window(HINSTANCE hInstance, LPCTSTR windowName, LPCTSTR windowTitle, int width, int height): hwnd(nullptr)
{
	this->hInstance = hInstance;
	this->windowName = windowName;
	this->windowTitle = windowTitle;
	this->m_Width = width;
	this->m_Height = height;
}

float Window::aspectRatio() const
{
	return static_cast<float>(m_Width) / static_cast<float>(m_Height);
}

HWND Window::GetHandle()
{
	if (!hwnd && !IntializeWindow()) {
		throw std::runtime_error("Failed to intialize Window. Please show this error message to the developers.");
	}
	return hwnd;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(0, "Are you a quitter?", "QUEST: A true quitter", MB_YESNO | MB_ICONQUESTION) == IDYES)
				DestroyWindow(hwnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

bool Window::IntializeWindow()
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "ERROR - could not register window class", "ERROR", MB_OK | MB_ICONERROR);
		return false;
	}

	//Attempt to create window handle
	hwnd = CreateWindowEx(NULL,
		windowName,
		windowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		m_Width, m_Height,
		NULL, NULL,
		hInstance, NULL);
	//if we failed, report it.
	if (!hwnd)
	{
		MessageBox(NULL, "ERROR - could not create window", "ERROR", MB_OK | MB_ICONERROR);
		return false;
	}

	//if everything went well, show the window.
	ShowWindow(hwnd, true);
	UpdateWindow(hwnd);

	return true;
}
