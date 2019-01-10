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

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// Unix platformy - pouzit ANSI escape kod pro mazani terminalu?
// Pokud neni definovano, pouzije se klasicky cyklus vypisujici znaky \b, \r
// Vyzkousejte co bude lepsi pro Vas terminal...
// #define UNIX_USE_ANSI_ESCAPE_CODE

// ================================================
// JE ZAKAZANO MODIFIKOVAT NASLEDUJICI CAST SOUBORU
// ================================================

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <Windows.h>
#else
#include <curses.h>  
#endif

#define CONSOLE_ROWS 25
#define CONSOLE_COLS 80

#define SCENE_WIDTH 20
#define SCENE_HEIGHT 12

/*
Framework namespace
 */
namespace Framework {

    /*
    Barvy do konzole
     */
    enum struct Color {
        CLR_NORMAL,
        CLR_NORMAL_FILL,
        CLR_RED,
        CLR_GREEN,
        CLR_BLUE,
        CLR_RED_FILL,
        CLR_GREEN_FILL,
        CLR_BLUE_FILL,
        CLR_MAGENTA_FILL,
        CLR_YELLOW_FILL,
        CLR_BLUE_L_FILL,
        CLR_DARK_GREEN_FILL,
        CLR_DARK_BROWN_FILL
    };

    /*
    Pozastavi provadeni programu na jednu sekundu.
     */
    void waitSec();
    /*
    Pozastavi provadeni programu na specifikovanou dobu (v sekundach).
     */
    void waitFor(double secs);

    /*
    Vykresli prostredi
     */
    void vypisProstredi(void* p, size_t rows, size_t cols);

    /*
    System namespace
     */
    namespace System {
        /*
        Inicializace konzole
         */
        void init();
        /*
        Vycisti konzoli
         */
        void clearConsole();
        /*
        Nastavi barvu vystupniho textu do konzole
         */
        unsigned short setConsoleColor(Color clr);
    }

} // /namespace Framework
#endif
