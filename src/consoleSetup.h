#ifndef CMDSWEEPER_CONSOLESETUP_H
#define CMDSWEEPER_CONSOLESETUP_H

namespace cmdsweeper {
    typedef int (*fgetch)();

    bool setupConsole();
    void getConsoleSize(int &width, int &height);
    fgetch getGetchFunc();

}
#endif //CMDSWEEPER_CONSOLESETUP_H
