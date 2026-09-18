#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter initial number of students (1 to 10): ";
    cin >> n;
    while (n < 1 || n > 10) {
        cout << "Invalid input. Enter a number between 1 and 10: ";
        cin >> n;
    }

    int* marks = new int[n];

    cout << "\nEnter initial marks:\n";
    for (int i = 0; i < n; i++) {
        cout << "Mark for student " << i + 1 << ": ";
        cin >> *(marks + i);
    }

    int newMark;
    cout << "\nEnter mark for the new student: ";
    cin >> newMark;

    int* temp = new int[n + 1];


//copying the old marks in the new dynamic array and adding the new mark at the end
    for (int i = 0; i < n; i++) {
        *(temp + i) = *(marks + i);
    }
    *(temp + n) = newMark;

    delete[] marks;
    marks = temp;
    n++;

    cout << "\nUpdated marks:\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << i + 1 << ": " << *(marks + i) << endl;
    }

    delete[] marks;
    marks = nullptr;

    return 0;
}