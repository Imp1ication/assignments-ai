#include "rc_game.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>

using std::string;
using std::bitset;
using std::cout;
using std::endl; 

/* Static member variables */
bitset<RCGame::MAX_BOARD_SIZE> *RCGame::rowMask_ = nullptr;
bitset<RCGame::MAX_BOARD_SIZE> *RCGame::columnMask_ = nullptr;
int RCGame::gameCounter_ = 0;

/* Constructor */
RCGame::RCGame(string inputFileName) {
    // Initialize board
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
            
            if (tmp == 1) {
                if (validRow_.find(i) == validRow_.end()) validRow_.insert(i);
                if (validColumn_.find(j) == validColumn_.end()) validColumn_.insert(j);
            }
        }
    }
    fin.close();

    // Initialize player data
    currentPlayer = 0;
    playerScore_[0] = playerScore_[1] = 0;

    // Initialize rowMask_ and columnMask_
    if (gameCounter_ == 0) {
        rowMask_ = new bitset<MAX_BOARD_SIZE>[row_];
        columnMask_ = new bitset<MAX_BOARD_SIZE>[column_];

        for (int i = 0; i < row_; ++i) {
            for (int j = 0; j < column_; ++j) {
                rowMask_[i].set(i * column_ + j);
                columnMask_[j].set(i * column_ + j);
            }
        }
    }
    gameCounter_ += 1;
}

/* Copy constructor */
RCGame::RCGame(const RCGame& game) {
    row_ = game.row_;
    column_ = game.column_;
    currentPlayer = game.currentPlayer;
    playerScore_[0] = game.playerScore_[0];
    playerScore_[1] = game.playerScore_[1];
    board_ = game.board_;
    validRow_ = game.validRow_;
    validColumn_ = game.validColumn_;

    gameCounter_ += 1;
}

/* Destructor */ 
RCGame::~RCGame() {
    gameCounter_ -= 1;
    if (gameCounter_ == 0) {
        delete[] rowMask_;
        delete[] columnMask_;
    }
}

/* Public member functions */
std::vector<RCMove> RCGame::getValidMoves() const {
    std::vector<RCMove> validMoves;

    for (int i : validRow_) {
        validMoves.push_back(RCMove(RowColumn::Row, i));
    }
    for (int i : validColumn_) {
        validMoves.push_back(RCMove(RowColumn::Column, i));
    }

    return validMoves;
}

bool RCGame::isLineEmpty(RCMove move) const {
    RowColumn rowColumn = move.first;
    int line = move.second;

    if (!isLineValid(move)) {
        return true;
    }

    if (rowColumn == RowColumn::Row) {
        return (board_ & rowMask_[line]).none();
    } else {
        return (board_ & columnMask_[line]).none();
    }
}

bool RCGame::isBoardEmpty() const {
    return board_.none();
}

int RCGame::countLine(RCMove move) const {
    RowColumn rowColumn = move.first;
    int line = move.second;

    if (!isLineValid(move)) { return -1; }
    if (isLineEmpty(move)) { return 0; }

    int count = 0;
    if (rowColumn == RowColumn::Row) {
        for (int i = 0; i < column_; ++i) {
            if (board_[line * column_ + i]) {
                ++count;
            }
        }
    } else {
        for (int i = 0; i < row_; ++i) {
            if (board_[i * column_ + line]) {
                ++count;
            }
        }
    }

    return count;
}

int RCGame::clearLine(RCMove move) {
    RowColumn rowColumn = move.first;
    int line = move.second;

    if (!isLineValid(move)) { return -1; }
    if (isLineEmpty(move)) { return 0; }

    int count = countLine(move);

    playerScore_[currentPlayer] += count;
    switchPlayer();

    if (rowColumn == RowColumn::Row) {
        board_ &= ~rowMask_[line];

        validRow_.erase(line);
        for (auto it = validColumn_.begin(); it != validColumn_.end(); ) {
            if (isLineEmpty(RCMove(RowColumn::Column, *it))) {
                it = validColumn_.erase(it);
            } else {
                ++it;
            }
        }
    } else {
        board_ &= ~columnMask_[line];

        validColumn_.erase(line);
        for (auto it = validRow_.begin(); it != validRow_.end(); ) {
            if (isLineEmpty(RCMove(RowColumn::Row, *it))) {
                it = validRow_.erase(it);
            } else {
                ++it;
            }
        }
    }

    return count;
}

void RCGame::printBoard() const {
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < column_; ++j) {
            cout << board_[i * column_ + j] << " ";
        }
        cout << endl;
    }
}

/* Private member functions */
bool RCGame::isLineValid(RCMove move) const {
    RowColumn rowColumn = move.first;
    int line = move.second;

    if (line <0 || line >= (rowColumn == RowColumn::Row ? row_ : column_)) {
        return false;
    }
    return true;
}

void RCGame::switchPlayer() {
    currentPlayer = 1 - currentPlayer;
}

/* Minimax optimization */
std::pair<RCMove, int> minimax(RCGame game,int depth, int alpha, int beta, int maximizingPlayer) {
    // std::cout << "depth: " << depth << std::endl;
    // game.printBoard();
    // std::cout << std::endl;

    // Initialize best move and best score 
    RCMove bestMove(RowColumn::Row, -1);
    int bestScore = (maximizingPlayer == game.getCurrentPlayer()) ? -RCGame::MAX_BOARD_SIZE : RCGame::MAX_BOARD_SIZE;

    // If hit leaf node, return best move and best score 
    if (depth == 0 || game.isBoardEmpty()) {
        bestScore = game.getPlayerScore(maximizingPlayer) - game.getPlayerScore(1 - maximizingPlayer);
        return std::make_pair(bestMove, bestScore);
    }

    // Get all valid validMoves
    std::vector<RCMove> validMoves = game.getValidMoves();

    for (RCMove move : validMoves) {
        // Make a copy of the game
        RCGame gameCopy(game);

        // Clear the line
        gameCopy.clearLine(move);

        // Recursively call minimax
        std::pair<RCMove, int> result = minimax(gameCopy, depth - 1, alpha, beta, maximizingPlayer);

        // Update best score and best move
        if (maximizingPlayer == game.getCurrentPlayer()) {
            if (result.second > bestScore) {
                bestScore = result.second;
                bestMove = move;
            }
            alpha = std::max(alpha, bestScore);
        } else {
            if (result.second < bestScore) {
                bestScore = result.second;
                bestMove = move;
            }
            beta = std::min(beta, bestScore);
        }

        // Alpha-beta pruning
        if (beta <= alpha) {
            break;
        }
    }

    return std::make_pair(bestMove, bestScore);
}
