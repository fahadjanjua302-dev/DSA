// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// Lab 06 - Task 5: Removing values from a linear array queue

#include <iostream>
using namespace std;

const int SIZE = 5;
int items[SIZE];
int front = -1;
int rear = -1;

void enqueue(int value) {
    if (rear == SIZE - 1) {
        cout << "Queue is full: cannot insert " << value << "." << endl;
        return;
    }
    if (front == -1)
        front = 0;
    items[++rear] = value;
    cout << "Inserted " << value << endl;
}

void dequeue() {
    if (front == -1) {
        cout << "Queue is empty: cannot remove." << endl;
        return;
    }
    cout << "Removed " << items[front] << endl;
    if (front == rear)                      // last item removed -> reset
        front = rear = -1;
    else
        front++;
}

void peekFront() {
    if (front == -1) {
        cout << "Queue is empty: nothing at front." << endl;
        return;
    }
    cout << "Front element: " << items[front] << endl;
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
    enqueue(10);
    enqueue(20);
    enqueue(30);
    dequeue();
    peekFront();
    display();

    cout << "\n--- Remove all remaining items ---" << endl;
    dequeue();
    dequeue();
    cout << "front = " << front << ", rear = " << rear << " (both -1 after reset)" << endl;
    dequeue();                              // removal from empty queue

    cout << "\n--- Insert 40 after reset ---" << endl;
    enqueue(40);
    peekFront();
    display();

    return 0;
}
