#include "rc_game.h"
#include <iostream>
#include <fstream>

using std::string;
using std::bitset;

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
            board_[i * column_ + j] = tmp;
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

/* Destructor */ 
RCGame::~RCGame() {
    delete[] rowMask_;
    delete[] columnMask_;
}

/* Public member functions */
bool RCGame::isRowEmpty(int row) const {
    if (!isValidPos(row, 0)) {
        throw std::out_of_range("Row index out of range");
    }

    return (board_ & rowMask_[row]).none();
}

bool RCGame::isColumnEmpty(int column) const {
    if (!isValidPos(0, column)) {
        throw std::out_of_range("Column index out of range");
    }

    return (board_ & columnMask_[column]).none();
}

bool RCGame::isBoardEmpty() const {
    return board_.none();
}

int RCGame::countRow(int row) const {
    if (!isValidPos(row, 0)) {
        throw std::out_of_range("Row index out of range");
    }

    int count = 0;

    for (int i = 0; i < column_; ++i) {
        if (board_[row * column_ + i]) {
            ++count;
        }
    }

    return count;
}

int RCGame::countColumn(int column) const {
    if (!isValidPos(0, column)) {
        throw std::out_of_range("Column index out of range");
    }

    int count = 0;
    for (int i = 0; i < row_; ++i) {
        if (board_[i * column_ + column]) {
            ++count;
        }
    }

    return count;
}

int RCGame::clearRow(int row) {
    if (!isValidPos(row, 0)) {
        throw std::out_of_range("Row index out of range");
    }

    if (isRowEmpty(row)) {
        return 0;
    }

    int count = countRow(row);
    rowClear_.push_back(row);
    board_ &= ~rowMask_[row];

    return count;
}

int RCGame::clearColumn(int column) {
    if (!isValidPos(0, column)) {
        throw std::out_of_range("Column index out of range");
    }

    if (isColumnEmpty(column)) {
        return -1;
    }

    int count = countColumn(column);
    columnClear_.push_back(column);
    board_ &= ~columnMask_[column];

    return count;
}

void RCGame::printBoard() const {
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < column_; ++j) {
            std::cout << board_[i * column_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

/* Private member functions */
bool RCGame::isValidPos(int row, int column) const {
    return row >= 0 && row < row_ && column >= 0 && column < column_;
}

