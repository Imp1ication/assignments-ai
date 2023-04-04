#include "targeted_therapy.h"
#include <iostream>
#include <vector>

/* Constructor */
TargetedTherapy::TargetedTherapy() : numMoves(0) {}

TargetedTherapy::TargetedTherapy(int num_cells) : cells(num_cells, 1), numMoves(0) {}

TargetedTherapy::TargetedTherapy(std::string board) : numMoves(0) {
    for (auto it : board) {
        if (it == '0') {
            cells.push_back(0);
        } else if (it == '1') {
            cells.push_back(1);
        }
    }
}

TargetedTherapy::TargetedTherapy(const TargetedTherapy& other) {
    cells = other.cells;
    stepRecord = other.stepRecord;
    numMoves = other.numMoves;
}

/* Getters and Setters */
int TargetedTherapy::getNumCells() const {
    return cells.size();
}

int TargetedTherapy::getNumMoves() const {
    return numMoves;
}

std::string TargetedTherapy::toString() {
    std::string board = "";
    for (auto it : cells) {
        board += std::to_string(it);
    }

    return board;
}

std::string TargetedTherapy::getBoard() const {
    std::string board = "";
    for (auto it : cells) {
        board += std::to_string(it) + " ";
    }
    return board;
}

std::string TargetedTherapy::getStepRecord() const {
    std::string record = "";
    for (auto it : stepRecord) {
        record += std::to_string(it) + " ";
    }
    return record;
}

/* Public Methods */
bool TargetedTherapy::destroyCell(int idx) {
    idx--;

    if (!isInBounds(idx) || cells[idx] == 0 || isGameOver()) { return false; }

    cells[idx] = 0;
    numMoves++;
    stepRecord.push_back(idx+1);

    // Split cells
    std::vector<tt_board> newCells;
    
    for (int i = 0; i < static_cast<int>(cells.size()); ++i) {
        if (cells[i] == 1) {
            tt_board newCell(cells.size(), 0);
            if (isInBounds(i - 1)) { newCell[i - 1] = 1; }
            if (isInBounds(i + 1)) { newCell[i + 1] = 1; }

            newCells.push_back(newCell);
        }

        cells[i] = 0;
    }

    // Merge cells
    for (auto it : newCells) {
        for (int i = 0; i < static_cast<int>(cells.size()); ++i) {
            cells[i] = cells[i] | it[i];
        }
    }
        
    return true;
}

bool TargetedTherapy::isGameOver() const {
    for (auto it : cells) {
        if (it == 1) { return false; }
    }
    return true;
}

void TargetedTherapy::printBoard() {
    std::cout << getBoard() << std::endl;
}

/* Private Methods */
bool TargetedTherapy::isInBounds(int i) {
    return i >= 0 && i < static_cast<int>(cells.size());
}
