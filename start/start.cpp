// start.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"

#include <string>
#include <vector>
#include <thread>
#include <atomic> 
#include <mutex>

using namespace std;

const string gStrTargetClassName = "PokerStarsTableFrameClass";
atomic<HWND> gTargetWindow = 0x0;

void Log(char * format, ...)
{
	char buffer[500];
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	printf("[0x%X]: %s\n", GetCurrentThreadId(), buffer);
	va_end(args);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	string strClassName("");
	strClassName.resize(MAX_PATH);

	if (!GetClassName(hwnd, (char*)strClassName.data(), strClassName.size()))
		Log("enum: 0x%X \t - false [GLN: 0x%X]\n", hwnd, GetLastError());
	else if (string::npos != strClassName.find(gStrTargetClassName.c_str()))
	{
		Log("enum: 0x%X \t %s \t I found It!\n", hwnd, strClassName.c_str());
		gTargetWindow.store(hwnd); 

		/*RECT wndPos = {};
		if (!GetWindowRect(hwnd, &wndPos))
		printf("enum: 0x%X \t - false [GWR: 0x%X]\n", hwnd, GetLastError());
		else
		{
		SetCursorPos(wndPos.left, wndPos.top);
		Sleep(1000);
		}*/
	}


	return TRUE;
}

atomic<bool> gNeedPrint = true;

void PrintCursorPos()
{
	Sleep(5000);

	HWND targetHWND = gTargetWindow.load();
	while (gNeedPrint.load())
	{
		LONG lStyle = GetWindowLong(targetHWND, GWL_STYLE);
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
		SetWindowLong(targetHWND, GWL_STYLE, lStyle);

		POINT pos = {};
		RECT wndRect = {};
		GetCursorPos(&pos);
		GetWindowRect(targetHWND, &wndRect);

		int x = pos.x - wndRect.left;
		int y = pos.y - wndRect.top;

		DWORD pose = 0x0;
		pose += x > 0 ? x : 0;
		pose += (y > 0 ? y : 0) << 16;

		SendMessage(targetHWND, WM_LBUTTONDOWN, 0x0, pose);
		Sleep(100);
		SendMessage(targetHWND, WM_LBUTTONUP, 0x0, pose);


		/*
		Sleep(1000);
		SendMessage(targetHWND, WM_RBUTTONUP, 0x0, pose);
		SendMessage(targetHWND, WM_RBUTTONDOWN, 0x0, pose);*/

		Log("pose: H:0x%X %d:%d - %d:%d = %d:%d [0x%X]", targetHWND, wndRect.left, wndRect.top, pos.x, pos.y, x, y, pose);
		Sleep(1000);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	EnumWindows(&EnumWindowsProc, 0x0);

	std::thread threadCursorPos(PrintCursorPos);
	threadCursorPos.detach();

	system("pause");

	gNeedPrint.store(false);

	return 0;
}

