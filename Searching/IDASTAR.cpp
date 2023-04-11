#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "targeted_therapy.h"

/* Constructor */
IDA::IDA(TargetedTherapy& frontier, int maxDepth) : frontier(frontier), maxDepth(maxDepth), searchTime(-1.0) {}

/* Getters and Setters */ 
TargetedTherapy IDA::getSolution() const { return solution; }

double IDA::getSearchTime() const { return searchTime; }

/* Public Methods */
bool IDA::search(int limit) {
    // start timer
    clock_t start = clock();

    // search
    bool found = false;
    for (int i = 0; i < maxDepth; i++) {
        std::cout << "Depth: " << i << std::endl;

        // clear visited 
        visited.clear();

        if ( dfs(frontier, i, limit) ) {
            found = true;
            break;
        }
    }

    // stop timer
    clock_t end = clock();
    searchTime = (double)(end - start) / CLOCKS_PER_SEC;

    return found;
}

/* Private Methods */
bool IDA::dfs(TargetedTherapy& frontier, int depth, int limit) {
    // check if frontier is in visited
    if (visited.find(frontier.toString()) != visited.end()) {
        if (visited[frontier.toString()] <= depth) {
            visited[frontier.toString()] = depth;
        } else {
            return false;
        }
    } else {
        visited[frontier.toString()] = depth;
    }

    // check if frontier is solution
    if (frontier.isGameOver()) {
        solution = frontier;
        return true;
    }

    // check if depth is 0
    if (depth == 0) {
        return false;
    }

    // get all possible moves
    std::vector<TargetedTherapy> moves;
    for (int i = 0; i < frontier.getNumCells(); ++i) {
        TargetedTherapy temp = frontier;

        if (temp.destroyCell(i+1)) {
            if ( heuristic(temp) <= limit )
                moves.push_back(temp);
        }
    }

    // sort moves by heuristic
    std::sort(moves.begin(), moves.end(), [this](TargetedTherapy a, TargetedTherapy b) {
        return heuristic(a) < heuristic(b);
    });

    // search
    for ( auto it : moves ) {
        if ( dfs(it, depth-1, limit) ) {
            return true;
        }
    }

    return false;
}

int IDA::heuristic(TargetedTherapy& frontier) {
    if (frontier.isGameOver()) {
        return 0;
    }

    std::string board = frontier.toString();
    int h = 0;

    for ( char c : board ) {
        if (c == '1') {
            h += 1;
        }
    }

    return frontier.getNumMoves() + h;
}

int main() {
    // Read the input file.
    std::ifstream infile("input.txt");

    if ( !infile.is_open() ) {
        std::cout << "Error: Cannot open the input file." << std::endl;
        return 1;
    }

    std::string input;

    getline(infile, input);
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    infile.close();

    // Run IDA.
    TargetedTherapy t(input);
    IDA ida(t, t.getNumCells() * 2);
    bool found = ida.search(t.getNumCells() * 2);

    // Write the output file.
    std::ofstream outfile("output.txt");

    if ( !outfile.is_open() ) {
        std::cout << "Error: Cannot open the output file." << std::endl;
        return 1;
    }

    outfile << "Total run time = " << ida.getSearchTime() << " seconds." << std::endl;
    
    if (found) {
        TargetedTherapy solution = ida.getSolution();
        outfile << "An optimal solutioan has " << solution.getNumMoves() << " moves:" << std::endl;
        outfile << solution.getStepRecord() << std::endl;
    } else {
        outfile << "There is no solution in depth " << t.getNumCells() * 2 << "." << std::endl;
    }

    std::cout << "Search Done." << std::endl;

    return 0;
}
