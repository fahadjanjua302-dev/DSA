// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// DSA Lab 03 - Task 2: Accessing a structure through a pointer

#include <iostream>
#include<string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

int main() {
    Student s1;
    s1.rollNo = 1111;
    s1.name = "Default";
    s1.marks = 100;

    Student* p1 = &s1;

    cout << "\nOriginal Student Details Displayed using Pointer.." << endl;
    cout << "ID: " << p1->rollNo << endl;
    cout << "Name: " << p1->name << endl;
    cout << "Marks: " << p1->marks << endl;

    cout << "\nEnter Student Details.." << endl;
    cout << "Roll Number: ";
    cin >> (*p1).rollNo;

    cout << "Name: ";
    getline(cin >> ws, p1->name);   // allows names containing spaces

    cout << "Marks: ";
    cin >> p1->marks;

    cout << "\nNew Student Details.." << endl;
    cout << "ID: " << p1->rollNo << endl;
    cout << "Name: " << p1->name << endl;
    cout << "Marks: " << p1->marks << endl;

    // Note: p1 points to the local variable s1 - never delete it,
    // deleting a pointer to a non-heap object is undefined behaviour.
    return 0;
}
