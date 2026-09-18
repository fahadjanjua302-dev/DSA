#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int n;

    // 1. Read and validate n
    cout << "Enter the number of students: ";
    cin >> n;
    while (n <= 0 || n >10) {
        cout << "Error; no allocation or mark input";
        return 1;
    }

    // Dynamic allocation
    int* marks = new int[n];

    cout << "Enter " << n << " marks (0 to 100):\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": ";
        cin >> *(marks + i);
    }

    // 2. Display marks, total, average, and pass count
    int total = 0;
    int passCount = 0;

    cout << "\nMarks: ";
    for (int i = 0; i < n; i++) {
        cout << *(marks + i) << " ";
        total += *(marks + i);
        if (*(marks + i) >= 50) {
            passCount++;
        }
    }

    // Explicit type casting ensures floating-point division
    double average = static_cast<double>(total) / n;

    cout << "\nTotal Marks: " << total;
    cout << "\nAverage Mark: " << fixed << setprecision(2) << average;
    cout << "\nPassCount: " << passCount << endl;

    // 3. Deallocate memory
    delete[] marks;
    marks = nullptr;

    return 0;
}