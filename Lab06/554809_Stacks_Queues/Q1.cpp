// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// Lab 06 - Task 1: Stack using an array

#include <iostream>
using namespace std;

const int SIZE = 5;
int items[SIZE];
int top = -1;               // -1 means the stack is empty

bool isEmpty() { return top == -1; }
bool isFull()  { return top == SIZE - 1; }

void push(int value) {
    if (isFull()) {
        cout << "Stack Overflow: cannot push " << value << " (stack is full)." << endl;
        return;
    }
    items[++top] = value;
    cout << "Pushed " << value << endl;
}

void pop() {
    if (isEmpty()) {
        cout << "Stack Underflow: cannot pop (stack is empty)." << endl;
        return;
    }
    cout << "Popped " << items[top] << endl;
    top--;
}

void peek() {
    if (isEmpty()) {
        cout << "Cannot peek: stack is empty." << endl;
        return;
    }
    cout << "Top element: " << items[top] << endl;
}

void display() {
    if (isEmpty()) {
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "Stack (top to bottom): ";
    for (int i = top; i >= 0; i--)
        cout << items[i] << " ";
    cout << endl;
}

int main() {
    cout << "--- Basic operations ---" << endl;
    push(10);
    push(20);
    push(30);
    display();
    pop();
    peek();
    display();

    cout << "\n--- Test: sixth insertion (overflow) ---" << endl;
    push(40);
    push(50);
    push(60);          // stack now full (5 items)
    push(70);          // sixth insertion -> blocked
    display();

    cout << "\n--- Test: pop after removing all values ---" << endl;
    while (!isEmpty())
        pop();
    pop();             // pop on empty stack
    peek();            // peek on empty stack
    display();

    return 0;
}
