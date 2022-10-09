#include "consoleSetup.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <windows.h>
#include <conio.h>
bool cmdsweeper::setupConsole() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return false;
    }

    SetConsoleOutputCP(CP_UTF8);
    return true;
}
cmdsweeper::fgetch cmdsweeper::getGetchFunc() {
    return getch;
}

void cmdsweeper::getConsoleSize(int &width, int &height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

#else

#include <iostream>
bool cmdsweeper::setupConsole() {
    std::cout << "ERROR: Non-Windows platform not yet supported\n";
    return false;
}

#endif
