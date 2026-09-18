#include <iostream>
using namespace std;

int main() {
    int sales[2][3];
    int (*rowPtr)[3] = sales;

    // 1. Read values into 2D array using pointer notation
    cout << "Enter non-negative sales values for 2 branches across 3 days:\n";
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 3; c++) {
            cout << "Branch " << r + 1 << ", Day " << c + 1 << ": ";
            cin >> *(*(rowPtr + r) + c);
        }
    }

    // Display values in a two-row table
    cout << "\nSales Table (Branch x Day):\n";
    for (int r = 0; r < 2; r++) {
        cout << "Branch " << r + 1 << ":\t";
        for (int c = 0; c < 3; c++) {
            cout << *(*(rowPtr + r) + c) << "\t";
        }
        cout << endl;
    }

    // 2. Branch Totals (Row Totals)
    cout << "\nBranch Totals:\n";
    for (int r = 0; r < 2; r++) {
        int branchTotal = 0;
        for (int c = 0; c < 3; c++) {
            branchTotal += *(*(rowPtr + r) + c);
        }
        cout << "Branch " << r + 1 << " Total: " << branchTotal << endl;
    }

    // Combined Daily Totals (Column Totals)
    cout << "\nCombined Daily Totals:\n";
    for (int c = 0; c < 3; c++) {
        int dayTotal = 0;
        for (int r = 0; r < 2; r++) {
            dayTotal += *(*(rowPtr + r) + c);
        }
        cout << "Day " << c + 1 << " Total: " << dayTotal << endl;
    }

    return 0;
}