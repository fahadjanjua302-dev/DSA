// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// DSA Lab 03 - Task 5: Checking whether a record exists

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

void displayIfExists(const Student* s) {
    if (s != nullptr) {
        displayStudent(s);
    }
    else {
        cout << "\nNo record Available" << endl;
    }
}

int main() {
    // 1. Initialize pointer explicitly to nullptr
    Student* s2 = nullptr;

    // Call 1: Before allocation
    cout << "--- Before Allocation ---";
    displayIfExists(s2);

    // 2. Allocate and enter record
    s2 = new Student{};

    cout << "\nEnter Student Details.." << endl;
    cout << "Roll Number: ";
    cin >> s2->rollNo;

    cout << "Name: ";
    getline(cin >> ws, s2->name);   // allows names containing spaces

    cout << "Marks: ";
    cin >> s2->marks;

    // Call 2: After allocating AND entering record
    cout << "\n--- After Allocation and Entering Record ---";
    displayIfExists(s2);

    // 3. Delete record and reset pointer
    delete s2;
    s2 = nullptr;

    // Call 3: After deleting and resetting to nullptr
    cout << "\n--- After Deleting and Resetting to nullptr ---";
    displayIfExists(s2);

    return 0;
}
