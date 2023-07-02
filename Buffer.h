#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

HANDLE hOutput, hOutBuf;
COORD coord = { 0, 0 };
DWORD bytes = 0;
bool flag = 0;

void initconsoleScreenBuffer()
{
	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);
}

void show(char map[20][20])
{
	if (flag == 0)
	{
		for (int i = 0; i < 20; i++)
		{
			coord.Y = i;
			WriteConsoleOutputCharacterA(hOutBuf, map[i], 20, coord, &bytes);
		}
		SetConsoleActiveScreenBuffer(hOutBuf);
	}
	else if (flag == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			coord.Y = i;
			WriteConsoleOutputCharacterA(hOutput, map[i], 20, coord, &bytes);
		}
		SetConsoleActiveScreenBuffer(hOutput);
	}
	if (flag == 0)
	{
		flag = 1;
	}
	else
	{
		flag = 0;
	}
}