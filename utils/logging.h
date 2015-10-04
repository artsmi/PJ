#pragma once

#include "windows.h"

#include <stdio.h>
#include <stdarg.h>

using namespace std;

namespace Logging
{
	void Log(char * format, ...);
}