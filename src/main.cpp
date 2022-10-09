#include <iostream>
#include "consoleSetup.h"
#include "cmdSweeper.h"

int main(int argc, char *argv[]) {
    if (!cmdsweeper::setupConsole()) {
        std::cout << "ERROR: Failed to setup console\n";
        return -1;
    }
    cmdsweeper::fgetch getch = cmdsweeper::getGetchFunc();
    int consoleWidth, consoleHeight;
    cmdsweeper::getConsoleSize(consoleWidth, consoleHeight);

    int width = (consoleWidth-3)/2;
    int height = consoleHeight-2;
    if (argc >= 2) {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
    }
    if (width <= 3 || height <= 3) {
        return 0;
    }
    int mines = (width * height)/8;
    cmdSweeper::CmdSweeper sweeper(width, height, mines, getch);

    return 0;
}
