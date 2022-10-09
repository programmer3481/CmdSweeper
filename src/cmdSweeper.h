#ifndef CMDSWEEPER_CMDSWEEPER_H
#define CMDSWEEPER_CMDSWEEPER_H

#include "consoleSetup.h"

namespace cmdSweeper {
    struct tile {
        bool isMine = false;
        bool isMarked = false;
        bool isDiscovered = false;
        bool isSelected = false;
        int number = 0;
    };

    class CmdSweeper {
    public:
        CmdSweeper(int width, int height, int nMines, cmdsweeper::fgetch getch);
        ~CmdSweeper();
    private:
        void printBorder() const;
        int width, height;
        tile* map;
        cmdsweeper::fgetch getch;

        int getMapIndex(int x, int y) const;
        void updateTile(int x, int y);
        void setMines(int n, int xExclude, int yExclude);
        void gameOverFunc();
        void gameWinFunc();
        bool discover(int x, int y);
        bool discoverAround(int x, int y);
        void showBombs();
    };
}

#endif //CMDSWEEPER_CMDSWEEPER_H
