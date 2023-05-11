#pragma once

#include <bitset>
#include <string>
#include <vector>

const int MAX_ROW = 8;
const int MAX_COLUMN = 8;
const int MAX_BOARD_SIZE = MAX_ROW * MAX_COLUMN;

class RCGame {
public:
    RCGame(std::string inputFileName);
    ~RCGame();

    int getHeight() const { return row_; }
    int getWidth() const { return column_; }

    bool isRowEmpty(int row) const;
    bool isColumnEmpty(int column) const;
    bool isBoardEmpty() const;

    int countRow(int row) const;
    int countColumn(int column) const;

    int clearRow(int row);
    int clearColumn(int column);
    
    void printBoard() const;

private:
    static std::bitset<MAX_BOARD_SIZE> *rowMask_, *columnMask_;

    int row_, column_;
    int playerScore_, aiScore_;

    std::bitset<MAX_BOARD_SIZE> board_;

    bool isValidPos(int row, int column) const;
};
