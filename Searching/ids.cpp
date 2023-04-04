#include "targeted_therapy.h"
#include <iostream>
#include <vector>
#include <unordered_map>

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

    // if frontier is not solution
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
