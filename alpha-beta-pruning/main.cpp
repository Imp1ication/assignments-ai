#include <iostream>
#include <bitset>
#include "rc_game.h"

using namespace std;
const int BOARD_SIZE = 8;

int main () {
    RCGame game("input.txt");
    game.printBoard();
    cout << "\n\n";

    for(int i=0; i<4; ++i){
        cout << (game.isColumnEmpty(i)?"true":"false") << endl;
        game.clearColumn(i);
        game.printBoard();
        cout << (game.isBoardEmpty()?"true":"false") << endl;
    }


    return 0;
}
