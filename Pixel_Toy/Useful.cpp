#include "Useful.h"

void RemoveScrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1 };
	SetConsoleScreenBufferSize(handle, new_size);
}

void SetWindow(int Width, int Height)
{
	COORD coord;
	coord.X = Width;
	coord.Y = Height;

	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

void Gotoxy(int x, int y)
{
	COORD Pos = { y, x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Gotoxy_(int x, int y)
{
	COORD Pos = { y * 2, x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void TextColor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void SetCursorType(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
HANDLE COUT = 0;
HANDLE CIN = 0;

void Click(int* x, int* y)
{
	DWORD mode;
	WORD key;
	COORD pos;
	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
	while (1)
	{
		if (BeInput())
		{
			switch (GetInput(&key, &pos))
			{
			case MOUSE_EVENT:
				*x = pos.Y;
				*y = pos.X;
				return;
			}
		}
	}
}

void Click_(int* x, int* y)
{
	DWORD mode;
	WORD key;
	COORD pos;
	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
	while (1)
	{
		if (BeInput())
		{
			switch (GetInput(&key, &pos))
			{
			case MOUSE_EVENT:
				*x = pos.Y;
				*y = pos.X / 2;
				return;
			}
		}
	}
}

void Click__(int* x, int* y)
{
	DWORD mode;
	WORD key;
	COORD pos;
	CIN = GetStdHandle(STD_INPUT_HANDLE);
	COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(CIN, &mode);
	SetConsoleMode(CIN, mode | ENABLE_MOUSE_INPUT);
	switch (GetInput(&key, &pos))
	{
	case MOUSE_EVENT:
		*x = pos.Y;
		*y = pos.X / 2;
		return;
	}
}

int BeInput()
{
	INPUT_RECORD input_record;
	DWORD input_count;
	PeekConsoleInput(CIN, &input_record, 1, &input_count);
	return input_count;
}

int GetInput(WORD* vkey, COORD* pos)
{
	INPUT_RECORD input_record;
	DWORD input_count;
	ReadConsoleInput(CIN, &input_record, 1, &input_count);
	switch (input_record.EventType)
	{
	case MOUSE_EVENT:
		if (pos && (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(COUT, &csbi);
			*pos = input_record.Event.MouseEvent.dwMousePosition;
			pos->X -= csbi.srWindow.Left;
			pos->Y -= csbi.srWindow.Top;
			return MOUSE_EVENT;
		}
		break;
	case KEY_EVENT:
		if (vkey && (input_record.Event.KeyEvent.bKeyDown))
		{
			*vkey = input_record.Event.KeyEvent.wVirtualKeyCode;
			return KEY_EVENT;
		}
	}
}