#pragma once

#include "windows.h"

#include "../utils/logging.h"

using namespace Logging;

class Window
{
	public :
		
		Window();
		~Window();

		bool Init(HWND handle);
		void Normilize();
		void SetActive();

	private :

		void Refresh();

		HWND mHandle;
		RECT mRect;
};