#pragma once

#include "windows.h"

#include "../utils/Logs.h"

using namespace Logging;

class Window
{
	public :
		
		Window();
		~Window();

		bool Init(HWND handle);

	private :

		HWND mHandle;
		RECT mRect;
};