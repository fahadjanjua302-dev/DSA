// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// DSA Lab 03 - Task 1: Creating a structure

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

    cout << "Enter Student Details.." << endl;
    cout << "Roll Number: ";
    cin >> s1.rollNo;

    cout << "Name: ";
    getline(cin >> ws, s1.name);   // allows names containing spaces

    cout << "Marks: ";
    cin >> s1.marks;

    cout << "\nStudent Details.." << endl;
    cout << "ID: " << s1.rollNo << endl;
    cout << "Name: " << s1.name << endl;
    cout << "Marks: " << s1.marks << endl;

    return 0;
}
