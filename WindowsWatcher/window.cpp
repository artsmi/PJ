#pragma once

#include "window.h"

Window::Window() :
	mHandle(0x0)
{
	memset(&mRect, 0, sizeof(mRect));
};

Window::~Window() {};

bool Window::Init(HWND handle)
{
	if (handle)
	{
		if (!GetWindowRect(handle, &mRect))
			Log(__FUNCTION__": GWR failed! hwnd = 0x%X GLR: 0x%X", handle, GetLastError);
		else
		{
			mHandle = handle;
			return true;
		}	
	}

	return false;
}

void Window::Refresh()
{
	if (!GetWindowRect(mHandle, &mRect))
		Log(__FUNCTION__": GWR failed! hwnd = 0x%X GLR: 0x%X", mHandle, GetLastError);
}

void Window::SetActive()
{
	//TODO: not work properly =(
	SetActiveWindow(mHandle);
	SendMessage(mHandle, WM_ACTIVATE, WA_CLICKACTIVE, 0x0);
	SetFocus(mHandle);
}

void Window::Normilize()
{
	RECT deskRect = {};
	GetWindowRect(GetDesktopWindow(), &deskRect);

	int xSize = mRect.right - mRect.left;
	int ySize = mRect.bottom - mRect.top;

	Log(__FUNCTION__": size %d %d", xSize, ySize);

	SetWindowPos(mHandle, 0x0, mRect.right - xSize, 0, xSize, ySize, 0x0);
	SetActive();

	Refresh();
}