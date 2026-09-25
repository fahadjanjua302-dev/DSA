// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// DSA Lab 03 - Task 4: Using functions with pointers

#include <iostream>
#include<string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

void displayStudent(const Student* s) {
    cout << "\nDisplaying the Dynamic Student Details through function.." << endl;
    cout << "ID: " << s->rollNo << endl;
    cout << "Name: " << s->name << endl;
    cout << "Marks: " << s->marks << endl;
}

void updateMarks(Student* s, float newMarks) {
    cout << "\nUpdating marks using function.\nNew Marks are: " << newMarks << endl;
    s->marks = newMarks;
}

int main() {
    Student* s2 = new Student{};

    // taking details input
    cout << "\nEnter Dynamic Student Details.." << endl;
    cout << "Roll Number: ";
    cin >> (*s2).rollNo;

    cout << "Name: ";
    getline(cin >> ws, s2->name);   // allows names containing spaces

    cout << "Marks: ";
    cin >> s2->marks;

    displayStudent(s2);

    // Ask the user for the new marks instead of hardcoding a value,
    // so the update genuinely reflects user input, with basic validation.
    float newMarks;
    cout << "\nEnter new Marks between 0 and 100: ";
    cin >> newMarks;
    while (newMarks < 0 || newMarks > 100) {
        cout << "Invalid marks, enter again: ";
        cin >> newMarks;
    }
    updateMarks(s2, newMarks);

    displayStudent(s2);

    // freeing the memory and setting pointer to nullptr
    delete s2;
    s2 = nullptr;

    return 0;
}
