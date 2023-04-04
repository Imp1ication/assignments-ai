#include <iostream>
#include "targeted_therapy.h"

using namespace std;

int main() {

    TargetedTherapy t(9);
    IDS ids(t, 20);
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
    
    


    return 0;
}
