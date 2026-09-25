// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// DSA Lab 03 - Task 3: Creating a record dynamically

#include <iostream>
#include<string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

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

    // displaying details
    cout << "\nDisplaying the Dynamic Student Details.." << endl;
    cout << "ID: " << s2->rollNo << endl;
    cout << "Name: " << s2->name << endl;
    cout << "Marks: " << s2->marks << endl;

    // freeing the memory and setting pointer to nullptr
    delete s2;
    s2 = nullptr;

    return 0;
}
