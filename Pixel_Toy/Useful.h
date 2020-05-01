#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mmsystem.h>
#include <Digitalv.h>
#include <process.h>

#pragma comment(lib, "winmm.lib")

/*
 *	Useful.c
 */
typedef enum
{
    NOCURSOR,
    SOLIDCURSOR,
    NORMALCURSOR
} CURSOR_TYPE;

void RemoveScrollbar();
void SetWindow(int Width, int Height);
void Gotoxy(int x, int y);
void Gotoxy_(int x, int y);
void TextColor(int color_number);
void SetCursorType(CURSOR_TYPE c);
void Click(int* x, int* y);
void Click_(int* x, int* y);
void Click__(int* x, int* y);
int BeInput();
int GetInput(WORD* vkey, COORD* pos);

const int kBlack = 0;
const int kBlue = 1;
const int kGreen = 2;
const int kAqua = 3;
const int kRed = 4;
const int kPurple = 5;
const int kYellow = 6;
const int kWhite = 7;
const int kGray = 8;
const int kLBlue = 9;
const int kLGreen = 10;
const int kLAqua = 11;
const int kLRed = 12;
const int kLPurple = 13;
const int kLYellow = 14;
const int kLWhite = 15;

/*textcolor(0x배경색글자색)
0 = 검정색       8 = 회색
1 = 파랑색       9 = 연한 파랑색
2 = 초록색       A = 연한 초록색
3 = 옥색         B = 연한 옥색
4 = 빨강색       C = 연한 빨강색
5 = 자주색       D = 연한 자주색
6 = 노랑색       E = 연한 노랑색
7 = 흰색         F = 밝은 흰색*/