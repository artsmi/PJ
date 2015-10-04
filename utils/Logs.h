#pragma once

#include "windows.h"

#include <stdio.h>
#include <stdarg.h>

using namespace std;

namespace Logging
{
	void Log(char * format, ...)
	{
		char buffer[500];
		va_list args;
		va_start(args, format);
		vsprintf(buffer, format, args);
		printf("[0x%X]: %s\n", GetCurrentThreadId(), buffer);
		va_end(args);
	}
}