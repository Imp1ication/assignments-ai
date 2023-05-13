#include <iostream>
#include <fstream>
#include <bitset>
#include <ostream>
#include "rc_game.h"

using namespace std;
const int BOARD_SIZE = 8;

int main () {
    RCGame game("input.txt");
    game.printBoard();
    cout << endl;

    clock_t start = clock();

    auto result = minimax(game, RCGame::MAX_ROW+RCGame::MAX_COLUMN, -RCGame::MAX_BOARD_SIZE, RCGame::MAX_BOARD_SIZE, game.getCurrentPlayer());

    clock_t end = clock();
    double searchTime = (double)(end - start) / CLOCKS_PER_SEC;
    
    // write result to output.txt
    ofstream outputFile;
    outputFile.open("output.txt");

    outputFile << (result.first.first == RowColumn::Row ? "Row" : "Column") 
               << " # : " << result.first.second + 1 << endl
               << result.second << " pints" << endl
               << "Total run time = " << searchTime << " seconds." << endl;

    cout << (result.first.first == RowColumn::Row ? "Row" : "Column") 
               << " # : " << result.first.second + 1 << endl
               << result.second << " pints" << endl
               << "Total run time = " << searchTime << " seconds." << endl;

    // test minimax
    // while (!game.isBoardEmpty()) {
    //     cout << "Player: " << game.getCurrentPlayer() << endl;
    //     auto result = minimax(game, MAX_ROW+MAX_COLUMN, -MAX_BOARD_SIZE, MAX_BOARD_SIZE, game.getCurrentPlayer());
    //     cout << "Move: " << (result.first.first == RowColumn::Row ? "Row" : "Column") 
    //          << " " << result.first.second+1 
    //          << " " << result.second << endl;
    //     game.clearLine(result.first);
    //     game.printBoard();
    //     cout << endl;
    // }
    return 0;
}
