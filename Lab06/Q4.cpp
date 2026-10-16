// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// Lab 06 - Task 4: Inserting values into a linear array queue

#include <iostream>
using namespace std;

const int SIZE = 5;
int items[SIZE];
int front = -1;
int rear = -1;

void enqueue(int value) {
    if (rear == SIZE - 1) {                 // linear queue: no wrap-around
        cout << "Queue is full: cannot insert " << value << "." << endl;
        return;
    }
    if (front == -1)                        // first insertion
        front = 0;
    items[++rear] = value;
    cout << "Inserted " << value << endl;
}

void display() {
    if (front == -1) {
        cout << "Queue is empty." << endl;
        return;
    }
    cout << "Queue (front to rear): ";
    for (int i = front; i <= rear; i++)
        cout << items[i] << " ";
    cout << endl;
}

int main() {
    cout << "--- Display on empty queue ---" << endl;
    display();

    cout << "\n--- Insert 10, 20, 30 ---" << endl;
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    cout << "\n--- Fill the queue, then one more insertion ---" << endl;
    enqueue(40);
    enqueue(50);
    display();
    enqueue(60);                            // blocked
    display();

    return 0;
}
