#include "targeted_therapy.h"
#include <iostream>
#include <vector>

/* Constructor */
IDS::IDS(TargetedTherapy& frontier, int maxDepth) : frontier(frontier), depth(-1), maxDepth(maxDepth), searchTime(-1.0) {}

/* Getters and Setters */ 
TargetedTherapy IDS::getSolution() const {
    return solution;
}

int IDS::getDepth() const {
    return depth;
}

double IDS::getSearchTime() const {
    return searchTime;
}

/* Public Methods */
bool IDS::search() {
    // TODO
}


/* Private Methods */
