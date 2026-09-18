#include <iostream>
using namespace std;

int main() {
    int sales[5];
    int sum = 0;
    int* p = sales;

    // 1. Read values and display total using pointer notation
    cout << "Enter 5 non-negative sales values:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Day " << i + 1 << " Sales: ";
        cin >> *(p + i);
    }

    cout << "\nOriginal Sales: ";
    for (int i = 0; i < 5; i++) {
        cout << *(p + i) << " ";
        sum += *(p + i);
    }
    cout << "\nOriginal Total: " << sum << endl;

    // 2. Add 2 to the third day's value (index 2) via pointer
    *(p + 2) += 2;

    sum = 0; // Reset sum
    cout << "\nUpdated Sales: ";
    for (int i = 0; i < 5; i++) {
        cout << *(p + i) << " ";
        sum += *(p + i);
    }
    cout << "\nUpdated Total: " << sum << endl;

    return 0;
}