#include <iostream>
using namespace std;

int main() {
    int rows, cols;

    cout << "Enter number of students: ";
    cin >> rows;
    while (rows <=0 ) {
        cout << "Number of students must be positive. Re-enter: ";
        cin >> rows;
    }

    cout << "Enter number of subjects: ";
    cin >> cols;
    while (cols <= 0 ) {
        cout << "Number of subjects must be positive. Re-enter: ";
        cin >> cols;
    }

    int** marks = new int*[rows];
    for (int r = 0; r < rows; r++) {
        marks[r] = new int[cols];
    }

    cout << "\nEnter marks (0 to 100):\n";
    for (int r = 0; r < rows; r++) {
        cout << "--- Student " << r + 1 << " ---\n";
        for (int c = 0; c < cols; c++) {
            cout << "Subject " << c + 1 << ": ";
            cin >> *(*(marks + r) + c);
        }
    }

    cout << "\n--- Marks Matrix ---\n";
    for (int r = 0; r < rows; r++) {
        cout << "Student " << r + 1 << ":\t";
        for (int c = 0; c < cols; c++) {
            cout << *(*(marks + r) + c) << "\t";
        }
        cout << endl;
    }

    int bestStudent = 1;
    int maxTotal = 0;

    cout << "\n--- Student Totals ---\n";
    for (int r = 0; r < rows; r++) {
        int studentTotal = 0;
        for (int c = 0; c < cols; c++) {
            studentTotal += *(*(marks + r) + c);
        }
        cout << "Student " << r + 1 << " Total: " << studentTotal << endl;

        if (r == 0 || studentTotal > maxTotal) {
            maxTotal = studentTotal;
            bestStudent = r + 1;
        }
    }

    cout << "\nTopStudent: " << bestStudent << " with " << maxTotal << " marks.\n";

    for (int r = 0; r < rows; r++) {
        delete[] marks[r];
    }
    delete[] marks;
    marks = nullptr;

    return 0;
}