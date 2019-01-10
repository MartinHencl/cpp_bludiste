// framework pro praci s konzoli, neni potreba studovat ani menit

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//                       !!!!!!!!!!!!!!!!!!!!!!!!!!
//                       !!! NEMÌNITELNÝ SOUBOR !!!
//                       !!!!!!!!!!!!!!!!!!!!!!!!!!
//
// Tento soubor obsahuje zadání a rozhaní, která není dovoleno mìnit !
// Jednotlivé implementace realizujte v nových souborech.
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include "framework.h"
#include <iostream>

using namespace std;

namespace Framework {

	namespace System {
#ifdef WIN32
		static HANDLE backbuffers[2];
		static bool firstOneIsActive;

		void init() {
			SMALL_RECT windowSize = { 0, 0, CONSOLE_COLS - 1, CONSOLE_ROWS - 1 };
			COORD bufferSize = { CONSOLE_COLS, CONSOLE_ROWS };

			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleWindowInfo(console, TRUE, &windowSize);
			SetConsoleScreenBufferSize(console, bufferSize);

			for (int i = 0; i < sizeof backbuffers / sizeof(HANDLE); i++)
				backbuffers[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, 0);

			firstOneIsActive = true;
		}

		void clearConsole() {
			COORD topLeft = { 0, 0 };
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;
			CONSOLE_CURSOR_INFO consoleCursorInfo = { 1, false };

			GetConsoleScreenBufferInfo(console, &screen);

			FillConsoleOutputCharacter(console, TEXT(' '), screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);

			SetConsoleCursorPosition(console, topLeft);
			SetConsoleCursorInfo(console, &consoleCursorInfo);
		}

		unsigned short setConsoleColor(Color clr) {
			switch (clr) {
			case Color::CLR_NORMAL:
				return 0; // FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;

			case Color::CLR_NORMAL_FILL:
				return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN;

			case Color::CLR_RED:
				return FOREGROUND_RED | FOREGROUND_INTENSITY;

			case Color::CLR_GREEN:
				return FOREGROUND_GREEN | FOREGROUND_INTENSITY;

			case Color::CLR_BLUE:
				return FOREGROUND_BLUE | FOREGROUND_INTENSITY;

			case Color::CLR_RED_FILL:
				return BACKGROUND_RED | FOREGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;

			case Color::CLR_GREEN_FILL:
				return FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

			case Color::CLR_BLUE_FILL:
				return FOREGROUND_BLUE | BACKGROUND_BLUE | FOREGROUND_INTENSITY;

			case Color::CLR_MAGENTA_FILL:
				return FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

			case Color::CLR_YELLOW_FILL:
				return FOREGROUND_RED | BACKGROUND_RED | FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

			case Color::CLR_BLUE_L_FILL:
				return FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;

			case Color::CLR_DARK_GREEN_FILL:
				return FOREGROUND_GREEN | BACKGROUND_GREEN;

			case Color::CLR_DARK_BROWN_FILL:
				return FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_GREEN;
			}

			return 0;
		}
#else

		void init() {
			WINDOW *w = initscr();
			cbreak();
			nodelay(w, TRUE);

			noecho();
			start_color();
			curs_set(0);
		}

		unsigned short setConsoleColor(Color clr) {
			return 0;
		}

		void clearConsole() {
#ifdef UNIX_USE_ANSI_ESCAPE_CODE
			cout << "\033[2J\033[1;1H";
#else
			for (int i = 0; i < CONSOLE_ROWS; i++) {
				for (int j = 0; j < CONSOLE_COLS; j++) {
					cout << "\b";
				}
				cout << "\r";
			}
#endif
			cout.flush();
		}
#endif
	} // /namespace System

	void waitSec() {
		waitFor(1.);
	}

	void waitFor(double secs) {
#ifdef WIN32
		SleepEx((DWORD)(secs * 1000), false);
#else
		clock_t begin = clock();
		while (clock() - begin < (CLOCKS_PER_SEC * secs));
#endif
	}

	void vypisProstredi(void* p, size_t rows, size_t cols) {
#ifdef WIN32
		CHAR_INFO consoleBuffer[CONSOLE_ROWS * CONSOLE_COLS];
		memset(&consoleBuffer, 0, sizeof consoleBuffer);
		WORD attr = 0;

#define SysNewline 
#define SysSetColor(x) attr = System::setConsoleColor(x)
#ifdef UNICODE
#define SysConWrite(x,y,ch,color) \
        consoleBuffer[(x) + CONSOLE_COLS * (y)].Char.UnicodeChar = (wchar_t)(ch); \
        consoleBuffer[(x) + CONSOLE_COLS * (y)].Attributes = (color);
#else // !UNICODE
#define SysConWrite(x,y,ch,color) \
        consoleBuffer[(x) + CONSOLE_COLS * (y)].Char.AsciiChar = (char)(ch); \
        consoleBuffer[(x) + CONSOLE_COLS * (y)].Attributes = (color);
#endif 
#define SysUnSetColor(x)
#else // !WIN32
#define SysSetColor(x) \
        attron(COLOR_PAIR(((int)x+1)))
#define SysUnSetColor(x) \
        attroff(COLOR_PAIR(((int)x+1)))        
#define SysConWrite(x,y,ch,color) \
        mvaddch(y,x,ch);
#define SysNewline cout << endl
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_WHITE, COLOR_WHITE);
		init_pair(3, COLOR_RED, COLOR_BLACK);
		init_pair(4, COLOR_GREEN, COLOR_BLACK);
		init_pair(5, COLOR_BLUE, COLOR_BLACK);
		init_pair(6, COLOR_RED, COLOR_RED);
		init_pair(7, COLOR_GREEN, COLOR_GREEN);
		init_pair(8, COLOR_BLUE, COLOR_BLUE);
		init_pair(9, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(10, COLOR_YELLOW, COLOR_YELLOW);
		init_pair(11, COLOR_CYAN, COLOR_CYAN);
		init_pair(12, COLOR_BLACK, COLOR_GREEN);
		init_pair(13, COLOR_BLACK, COLOR_YELLOW);

		clear();
		attron(A_BOLD);
#endif
		int outx, outy;

#define pvalid(x, y) ((x) >= 0 && (y) >= 0 && (x) < cols && (y) < rows)
#define pget(p, x, y) (*(((char*) (p)) + cols * (y) + (x)))

		outy = 0;
		for (size_t y = 0; y < rows; y++) {
			outx = 0;
			for (size_t x = 0; x < cols; x++) {
				char ch = pget(p, x, y);
				Color c = Color::CLR_GREEN_FILL;
				switch (ch) {
				case 'R': c = Color::CLR_RED_FILL;
					break;
				case 'B': c = Color::CLR_BLUE_FILL;
					break;
				case 'b': c = Color::CLR_BLUE_L_FILL;
					break;
				case 'N': c = Color::CLR_NORMAL_FILL;
					break;
				case 'n': c = Color::CLR_NORMAL;
					break;
				case 'G': c = Color::CLR_GREEN_FILL;
					break;
				case 'Y': c = Color::CLR_YELLOW_FILL;
					break;
				case 'M': c = Color::CLR_MAGENTA_FILL;
					break;
				}

				SysSetColor(c);
				SysConWrite(outx, outy, ch, attr);
				/*SysConWrite(outx, outy + 1, ch, attr);
				SysConWrite(outx + 1, outy, ch, attr);
				SysConWrite(outx + 1, outy + 1, ch, attr);

				SysConWrite(outx + 2, outy, ch, attr);
				SysConWrite(outx + 2, outy + 1, ch, attr);
				SysConWrite(outx + 3, outy, ch, attr);
				SysConWrite(outx + 3, outy + 1, ch, attr);*/
				SysUnSetColor(c);

				outx++;
				/*outx++;
				outx++;
				outx++;*/
			}

			outy++;
			/*outy++;*/
		}

		// flush buffers...
#ifdef WIN32
		COORD characterBufferSize = { CONSOLE_COLS, CONSOLE_ROWS };
		COORD characterPosition = { 0, 0 };
		SMALL_RECT consoleWriteArea = { 0, 0, CONSOLE_COLS - 1, CONSOLE_ROWS - 1 };

		WriteConsoleOutput(Framework::System::backbuffers[!Framework::System::firstOneIsActive], consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
		SetConsoleActiveScreenBuffer(Framework::System::backbuffers[!Framework::System::firstOneIsActive]);
		Framework::System::firstOneIsActive = !Framework::System::firstOneIsActive;
		//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

		CONSOLE_CURSOR_INFO consoleCursorInfo = { 1, false };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
#else
		refresh();
#endif
	}

} // /namespace Framework
