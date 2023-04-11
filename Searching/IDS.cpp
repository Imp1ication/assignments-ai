#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "targeted_therapy.h"

/* Constructor */
IDS::IDS(TargetedTherapy& frontier, int maxDepth) : frontier(frontier), maxDepth(maxDepth), searchTime(-1.0) {}

/* Getters and Setters */ 
TargetedTherapy IDS::getSolution() const { return solution; }

double IDS::getSearchTime() const { return searchTime; }

/* Public Methods */
bool IDS::search() {

    // start timer
    clock_t start = clock();

    // search
    bool found = false;
    for (int i = 0; i < maxDepth; i++) {
        std::cout << "Depth: " << i << std::endl;

        // clear visited 
        visited.clear();

        if ( dfs(frontier, i) ) {
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
bool IDS::dfs(TargetedTherapy& frontier, int depth) {
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

    // if frontier is not solution, then expand frontier and search each child
    for (int i = 0; i < frontier.getNumCells(); ++i) {
        TargetedTherapy child = frontier;

        if ( child.destroyCell(i+1) ) {
            if ( dfs(child, depth - 1) ) {
                return true;
            }
        }
    }

    return false;
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

    // Run IDS.
    TargetedTherapy t(input);
    IDS ids(t, t.getNumCells() * 2);
    bool found = ids.search();

    // Write the output file.
    std::ofstream outfile("output.txt");

    if ( !outfile.is_open() ) {
        std::cout << "Error: Cannot open the output file." << std::endl;
        return 1;
    }

    outfile << "Total run time = " << ids.getSearchTime() << " seconds." << std::endl;
    
    if (found) {
        TargetedTherapy solution = ids.getSolution();
        outfile << "An optimal solutioan has " << solution.getNumMoves() << " moves:" << std::endl;
        outfile << solution.getStepRecord() << std::endl;
    } else {
        outfile << "There is no solution." << std::endl;
    }

    std::cout << "Search Done." << std::endl;

    return 0;
}
