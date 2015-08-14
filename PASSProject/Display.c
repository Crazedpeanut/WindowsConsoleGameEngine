#include <Windows.h>
#include <stdio.h>
#include "Display.h"
#include <conio.h>

void gotoxy(int x, int y);

char window_buffer[WINDOW_WIDTH][WINDOW_HEIGHT];

void init_display()
{
	system("mode con:cols=80 lines=25");
	clear_window();
}

void clear_window()
{
	int j, i;

	system("cls");

	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++)
		{
			window_buffer[j][i] = ' ';
		}
	}
}

void refresh()
{
	int i, j;

	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++)
		{
			gotoxy(j, i);
			printf("%c", window_buffer[j][i]);
		}
	}

	refresh();
}

void draw_char(int x, int y, char c)
{
	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
		window_buffer[x][y] = c;

#ifndef DEBUG
		gotoxy(x, y);
		printf("%c", c);
#endif // !DEBUG

	}
}

void draw_string(int x, int y, char *s)
{
	int i;

	for (i = 0; i < strlen(s); i++)
	{
		draw_char(x + i, y, s[i]);
	}
}

void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(handle, coord);
}

char get_user_input()
{
	if (_kbhit())
	{ 
		return _getch();
	}
	else
	{
		return '\0';
	}
}