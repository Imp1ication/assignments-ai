#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::vector<uint8_t> tt_board;

class TargetedTherapy {
public:
    TargetedTherapy();
    TargetedTherapy(int num_cells);
    TargetedTherapy(std::string board);
    TargetedTherapy(const TargetedTherapy& other);

    int getNumCells() const;
    int getNumMoves() const;
    std::string getBoard() const;
    std::string getStepRecord() const;

    bool destroyCell(int idx);
    bool isGameOver() const;

    std::string toString();
    void printBoard();

private:
    tt_board cells;
    std::vector<int> stepRecord;
    int numMoves;

    bool isInBounds(int i);
};

class IDS {
public:
    IDS(TargetedTherapy& frontier, int maxDepth); // if maxDepth < 0, then search until solution is found

    TargetedTherapy getSolution() const; // Returns empty TargetedTherapy if search is not performed
    double getSearchTime() const; // Returns -1 if search is not performed

    bool search(); // Returns true if solution is found

private:
    TargetedTherapy frontier, solution;
    int maxDepth;
    double searchTime;
    std::unordered_map<std::string, int> visited;

    bool dfs(TargetedTherapy& frontier, int depth);
};

class IDA {
public:
    IDA(TargetedTherapy& frontier, int maxDepth); // if maxDepth < 0, then search until solution is found

    TargetedTherapy getSolution() const; // Returns empty TargetedTherapy if search is not performed
    double getSearchTime() const; // Returns -1 if search is not performed

    bool search(int limit); // Returns true if solution is found

private:
    TargetedTherapy frontier, solution;
    int maxDepth;
    double searchTime;
    std::unordered_map<std::string, int> visited;

    bool dfs(TargetedTherapy& frontier, int depth, int limit);
    int heuristic(TargetedTherapy& frontier);
};

