#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main() {
    srand(time(NULL));

    ofstream fout("input.txt");

    if (!fout) {
        cout << "Error: cannot open file" << endl;
        return 1;
    }

    int length = rand() % 15 + 1;
    for (int i = 0; i < length; i++) {
        fout << rand() % 2;
        if (i != length - 1) { fout << " "; }
    }
    
    fout.close();
    return 0;
}
