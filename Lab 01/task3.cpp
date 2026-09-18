#include <iostream>

using namespace std;

class Student{
    public:
     int rollNumber;
     int marks;
    
    
     void display(){
         cout<<"Roll Number : "<<rollNumber<<endl;
         cout<<"Marks : "<<marks<<endl<<endl;
     }
     
};
int main() {
    
    Student s1;
    Student s2;
    
    s1.rollNumber=1;
    s1.marks=75;
    
    s2.rollNumber=2;
    s2.marks=90;
    
    s1.display();
    s2.display();

    
    s1.marks = 80;

    cout << "After Changing s1.marks to 80" << endl;
    s1.display();
    s2.display();

    return 0;
}
