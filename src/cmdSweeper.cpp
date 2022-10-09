#include "cmdSweeper.h"

#include <iostream>

namespace cmdSweeper {
    CmdSweeper::CmdSweeper(int width, int height, int nMines, cmdsweeper::fgetch getch) {
        this->width = width;
        this->height = height;
        this->getch = getch;
        this->map = new tile[width*height];

        std::cout << "\x1b[?1049h";
        std::cout << "\x1b[2J";
        std::cout << "\x1b[1;1H";
        printBorder();

        int xPos = 0, yPos = 0;
        map[0].isSelected = true;
        updateTile(0, 0);

        bool breakLoop = false;
        while (true) {
            int key = getch();
            map[getMapIndex(xPos, yPos)].isSelected = false;
            updateTile(xPos, yPos);
            switch (key) {
                case int('w'):
                    if (yPos > 0) {
                        yPos--;
                    }
                    break;
                case int('a'):
                    if (xPos > 0) {
                        xPos--;
                    }
                    break;
                case int('s'):
                    if (yPos < height - 1) {
                        yPos++;
                    }
                    break;
                case int('d'):
                    if (xPos < width - 1) {
                        xPos++;
                    }
                    break;
                case int('n'):
                    breakLoop = true;
                    break;
                default:
                    break;
            }
            map[getMapIndex(xPos, yPos)].isSelected = true;
            updateTile(xPos, yPos);
            if (breakLoop) {
                break;
            }
        }
        setMines(nMines, xPos, yPos);
        discover(xPos, yPos);

        bool gameOver = false;
        bool gameWin = false;
        while (true) {
            int key = getch();
            map[getMapIndex(xPos, yPos)].isSelected = false;
            updateTile(xPos, yPos);
            switch (key) {
                case int('w'):
                    if (yPos > 0) {
                        yPos--;
                    }
                    break;
                case int('a'):
                    if (xPos > 0) {
                        xPos--;
                    }
                    break;
                case int('s'):
                    if (yPos < height - 1) {
                        yPos++;
                    }
                    break;
                case int('d'):
                    if (xPos < width - 1) {
                        xPos++;
                    }
                    break;
                case int('n'):
                    if (map[getMapIndex(xPos, yPos)].isDiscovered ? !discoverAround(xPos, yPos) : !discover(xPos, yPos)) {
                        gameOver = true;
                    }
                    else {
                        gameWin = true;
                        for (int x = 0; x < width; ++x) {
                            for (int y = 0; y < height; ++y) {
                                if (map[getMapIndex(x, y)].isMine == map[getMapIndex(x, y)].isDiscovered) {
                                    gameWin = false;
                                    break;
                                }
                            }
                            if (!gameWin) {
                                break;
                            }
                        }
                    }
                    break;
                case int('m'):
                    map[getMapIndex(xPos, yPos)].isMarked = !map[getMapIndex(xPos, yPos)].isMarked;
                    break;
                default:
                    break;
            }
            map[getMapIndex(xPos, yPos)].isSelected = true;
            updateTile(xPos, yPos);
            if (gameOver || gameWin) {
                break;
            }
        }

        if (gameOver) {
            gameOverFunc();
        }
        else if (gameWin) {
            gameWinFunc();
        }
    }

    CmdSweeper::~CmdSweeper() {
        delete[] map;

        std::cout << "\x1b[2J";
        std::cout << "\x1b[?1049l";
        std::cout << "hello outside alternate buffer!";
    }

    void CmdSweeper::printBorder() const {
        std::cout << "\x1b[1;1H";
        std::cout << "\x1b(0";
        int wSize = width * 2 + 1;
        int hSize = height;

        std::cout << "l";
        for (int i = 0; i < wSize; ++i) {
            std::cout << "q";
        }
        std::cout << "k";
        for (int i = 0; i < hSize; ++i) {
            std::cout << "\x1b[1D\x1b[1Bx";
        }
        std::cout << "\x1b[1D\x1b[1Bj";
        for (int i = 0; i < wSize; ++i) {
            std::cout << "\x1b[2Dq";
        }
        std::cout << "\x1b[2Dm";
        for (int i = 0; i < hSize; ++i) {
            std::cout << "\x1b[1D\x1b[1Ax";
        }
        std::cout << "\x1b(B";
    }

    int CmdSweeper::getMapIndex(int x, int y) const {
        return x + y * width;
    }

    void CmdSweeper::gameOverFunc() {
        showBombs();
        std::cout << "\x1b[1;1H";
        std::cout << "GAME OVER";
        getch();
    }

    void CmdSweeper::gameWinFunc() {
        std::cout << "\x1b[1;1H";
        std::cout << "YOU WIN";
        getch();
    }

    bool CmdSweeper::discoverAround(int x, int y) {
        bool mine = true;
        if (x > 0) {
            mine &= discover(x-1, y);
            if (y > 0) {
                mine &= discover(x-1, y-1);
            }
            if (y < height-1) {
                mine &= discover(x-1, y+1);
            }
        }
        if (x < width-1) {
            mine &= discover(x+1, y);
            if (y > 0) {
                mine &= discover(x+1, y-1);
            }
            if (y < height-1) {
                mine &= discover(x+1, y+1);
            }
        }
        if (y > 0) {
            mine &= discover(x, y-1);
        }
        if (y < height-1) {
            mine &= discover(x, y+1);
        }
        return mine;
    }

    bool CmdSweeper::discover(int x, int y) {
        tile &t = map[getMapIndex(x, y)];
        if (t.isMarked || t.isDiscovered) {
            return true;
        }
        if (t.isMine) {
            return false;
        }
        t.isDiscovered = true;
        updateTile(x, y);
        if (t.number) {
            return true;
        }

        if (x > 0) {
            discover(x-1, y);
            if (y > 0) {
                discover(x-1, y-1);
            }
            if (y < height-1) {
                discover(x-1, y+1);
            }
        }
        if (x < width-1) {
            discover(x+1, y);
            if (y > 0) {
                discover(x+1, y-1);
            }
            if (y < height-1) {
                discover(x+1, y+1);
            }
        }
        if (y > 0) {
            discover(x, y-1);
        }
        if (y < height-1) {
            discover(x, y+1);
        }
        return true;
    }

    void CmdSweeper::setMines(int n, int xExclude, int yExclude) {
        srand((unsigned) time(nullptr));
        int i = 0;
        while (true) {
            int x = rand() % width;
            int y = rand() % height;
            if (map[getMapIndex(x, y)].isMine || ((x-1 <= xExclude && x+1 >= xExclude) && (y-1 <= yExclude && y+1 >= yExclude))) {
                continue;
            }
            else {
                map[getMapIndex(x, y)].isMine = true;
                if (x > 0) {
                    map[getMapIndex(x-1, y)].number++;
                    if (y > 0) {
                        map[getMapIndex(x-1, y-1)].number++;
                    }
                    if (y < height-1) {
                        map[getMapIndex(x-1, y+1)].number++;
                    }
                }
                if (x < width-1) {
                    map[getMapIndex(x+1, y)].number++;
                    if (y > 0) {
                        map[getMapIndex(x+1, y-1)].number++;
                    }
                    if (y < height-1) {
                        map[getMapIndex(x+1, y+1)].number++;
                    }
                }
                if (y > 0) {
                    map[getMapIndex(x, y-1)].number++;
                }
                if (y < height-1) {
                    map[getMapIndex(x, y+1)].number++;
                }
                i++;
            }
            if (i >= n) {
                break;
            }
        }
    }

    void CmdSweeper::showBombs() {
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (map[getMapIndex(x, y)].isMine) {
                    std::cout << "\x1b[" << (y+2) << ";" << (x*2 + 3) << "H";
                    std::cout << "+";
                }
            }
        }
    }

    void CmdSweeper::updateTile(int x, int y) {
        tile &t = map[getMapIndex(x, y)];
        std::cout << "\x1b[" << (y+2) << ";" << (x*2 + 2) << "H";
        if (x > 0 && map[getMapIndex(x - 1, y)].isDiscovered) {
            if (t.isDiscovered) {
                std::cout << "█";
            }
            else {
                std::cout << "▌";
            }
        }
        else {
            if (t.isDiscovered) {
                std::cout << "▐";
            }
            else {
                std::cout << " ";
            }
        }

        if (t.isDiscovered) {
            if (!t.isSelected) std::cout << "\x1b[7m";
            if (t.number) {
                std::cout << t.number;
            }
            else {
                std::cout << " ";
            }
        }
        else {
            if (t.isSelected) std::cout << "\x1b[7m";
            if (t.isMarked) {
                std::cout << "*";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "\x1b[27m";

        if (x + 1 < width && map[getMapIndex(x + 1, y)].isDiscovered) {
            if (t.isDiscovered) {
                std::cout << "█";
            }
            else {
                std::cout << "▐";
            }
        }
        else {
            if (t.isDiscovered) {
                std::cout << "▌";
            }
            else {
                std::cout << " ";
            }
        }
    }
}