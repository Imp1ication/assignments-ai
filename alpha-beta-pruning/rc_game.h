#pragma once

#include <cstdint>
#include <string>
#include <bitset>
#include <unordered_set>
#include <vector>

enum class RowColumn { Row, Column };
typedef std::pair<RowColumn, int> RCMove;

class RCGame {
public:
    static constexpr int MAX_ROW = 8;
    static constexpr int MAX_COLUMN = 8;
    static constexpr int MAX_BOARD_SIZE = MAX_ROW * MAX_COLUMN;

    RCGame(std::string inputFileName);
    RCGame(const RCGame& game);
    ~RCGame();

    int getHeight() const { return row_; }
    int getWidth() const { return column_; }
    int getPlayerScore(int player) const { return playerScore_[player]; }
    int getCurrentPlayer() const { return currentPlayer; }
    std::vector<RCMove> getValidMoves() const;

    bool isLineEmpty(RCMove move) const;
    bool isBoardEmpty() const;

    int countLine(RCMove move) const;
    int clearLine(RCMove move);

    // return <move, score>
    static std::pair<RCMove, int> minimax(RCGame game,int depth, int alpha, int beta, int maximizingPlayer); 

    void printBoard() const;

private:
    static std::bitset<MAX_BOARD_SIZE> *rowMask_, *columnMask_;
    static int gameCounter_;

    int row_, column_;
    int currentPlayer, playerScore_[2];

    std::bitset<MAX_BOARD_SIZE> board_;
    std::unordered_set<int> validRow_, validColumn_;

    bool isLineValid(RCMove move) const;
    void switchPlayer();
};

class RCGameManager {
public:
    void printTitle();
    bool run();

    void pressAnyKeyToContinue();
    
private:
    std::string highlightSelection(std::string text, int width);
    void printMenu(std::string title, std::vector<std::string> menu, size_t choice);
    void startGame();
    void pvpGame();
    void pvcGame(bool isPlayerFirst);
    void startRandomGame();
    void testAlphaBetaPruning();
    void quitGame();
    
};


