#include <cstddef>
#include <curses.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <ostream>
#include "rc_game.h"


#include <ncurses.h>

using namespace std;

int main () {
    RCGameManager GM;

    // Print title
    GM.printTitle();
    cout << endl;
    GM.pressAnyKeyToContinue();

    // Start Menu
    while (GM.run());
    return 0;
}
