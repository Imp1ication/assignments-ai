#include <iostream>
#include "targeted_therapy.h"

using namespace std;

int main() {
    TargetedTherapy t1("1010");
    IDS ids(t1, 2);
    

    cout << ids.getDepth() << endl;
    cout << ids.getSearchTime() << endl;

    return 0;
}
