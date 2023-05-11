#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

typedef std::unordered_map<uint8_t, uint8_t> Line;

const int MAX_WIDTH = 8, MAX_HEIGHT = 8;
const int MAX_BOARD_SIZE = MAX_WIDTH * MAX_HEIGHT;


class RCGame {
public: 
    RCGame(std::string inputFileName);
    ~RCGame();

    int getHeight() const { return row_; }
    int getWidth() const { return column_; }

    bool isRowEmpty(int row) const;
    bool isColumnEmpty(int column) const;
    bool isGameOver() const;

    int countRow(int row) const;
    int countColumn(int column) const;

    int clearRow(int row);
    int clearColumn(int column);

    void printBoard() const;

private:
    int row_, column_;
    int playerScore_, aiScore_;
    Line rowLine_, columnLine_; 

};
