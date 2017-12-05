#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, LPCTSTR windowName, LPCTSTR windowTitle, int width, int height);
	HWND GetHandle();
	UINT width() const { return m_Width; }
	UINT height() const { return m_Height; }
	float aspectRatio() const;
private:
	HINSTANCE hInstance;
	LPCTSTR windowName;
	LPCTSTR windowTitle;
	UINT m_Width;
	UINT m_Height;
	HWND hwnd;

	//static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool IntializeWindow();
};