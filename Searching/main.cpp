#include <iostream>
#include "targeted_therapy.h"

using namespace std;

void idss(int num, int max) {
    TargetedTherapy t(num);
    IDS ids(t, max);
    cout << "Q = " << t.getBoard() << endl;

    if (ids.search()) {
        TargetedTherapy solution = ids.getSolution();

        cout << "Total run time = " << ids.getSearchTime() << " seconds." << endl;
        cout << "An optimal solutioan has " << solution.getNumMoves() << " moves:" << endl;
        cout << solution.getStepRecord() << endl;
    } else {
        cout << "Total run time = " << ids.getSearchTime() << " seconds." << endl;
        cout << "There is no solution." << endl;
    }

    cout << endl;
}

void idaa(int num, int max) {
    TargetedTherapy t(num);
    IDA ida(t, max);
    cout << "Q = " << t.getBoard() << endl;

    if (ida.search(max)) {
        TargetedTherapy solution = ida.getSolution();

        cout << "Total run time = " << ida.getSearchTime() << " seconds." << endl;
        cout << "An optimal solutioan has " << solution.getNumMoves() << " moves:" << endl;
        cout << solution.getStepRecord() << endl;
    } else {
        cout << "Total run time = " << ida.getSearchTime() << " seconds." << endl;
        cout << "There is no solution." << endl;
    }

    cout << endl;
}

int main() {
    int num = 25;
    for(int i = 1; i<15; ++i){
        cout << "i = " << i << endl;
        int max = i * 2;
        idss(i, max);
        idaa(i, max);
    }

    return 0;
}

