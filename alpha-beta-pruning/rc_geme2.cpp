#include "rc_game2.h"
#include <iostream>
#include <fstream>

using std::string;

/* Constructor */
RCGame::RCGame(string inputFileName) {
    std::ifstream fin(inputFileName);
    if(!fin) {
        std::cerr << "Cannot open " << inputFileName << "!" << std::endl;
        return;
    }

    fin >> row_ >> column_;

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < column_; ++j) {
            int tmp;
            fin >> tmp;
            if(tmp == 1) {
                rowLine_[i] += 1;

            } else continue;
        }
    }

    // Initialize rowMask_ and columnMask_
    rowMask_ = new bitset<MAX_BOARD_SIZE>[row_];
    columnMask_ = new bitset<MAX_BOARD_SIZE>[column_];

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < column_; ++j) {
            rowMask_[i].set(i * column_ + j);
            columnMask_[j].set(i * column_ + j);
        }
    }

    fin.close();

}
