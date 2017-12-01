#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, LPCTSTR windowName, LPCTSTR windowTitle, int nShowCmd, int width, int height, bool fullscreen);
	HWND GetHandle();
	bool GetFullscreen();
	UINT width() const { return m_Width; }
	UINT height() const { return m_Height; }
private:
	HINSTANCE hInstance;
	LPCTSTR windowName;
	LPCTSTR windowTitle;
	UINT m_Width;
	UINT m_Height;
	int nShowCmd;
	bool fullscreen;
	HWND hwnd;

	//static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool IntializeWindow();
};