#include "window.h"

Window::Window() :
	mHandle(0x0)
{
	memset(&mRect, 0, sizeof(mRect));
};

Window::~Window() {};

bool Window::Init(HWND handle)
{
	if (!handle)
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
