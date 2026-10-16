// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// Lab 06 - Task 2: Stack using a singly linked list

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* top = nullptr;        // head of the list acts as the top of the stack

bool isEmpty() { return top == nullptr; }

void push(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = top;    // insert at the head
    top = newNode;
    cout << "Pushed " << value << endl;
}

void pop() {
    if (isEmpty()) {
        cout << "Stack Underflow: cannot pop (stack is empty)." << endl;
        return;
    }
    Node* temp = top;
    cout << "Popped " << temp->data << endl;
    top = top->next;        // remove from the head
    delete temp;
}

void peek() {
    if (isEmpty()) {
        cout << "Cannot peek: stack is empty." << endl;
        return;
    }
    cout << "Top element: " << top->data << endl;
}

void display() {
    if (isEmpty()) {
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "Stack (top to bottom): ";
    for (Node* cur = top; cur != nullptr; cur = cur->next)
        cout << cur->data << " ";
    cout << endl;
}

void releaseAll() {          // free every remaining node
    while (top != nullptr) {
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

int main() {
    push(5);
    push(15);
    push(25);
    display();
    pop();
    peek();
    display();

    cout << "\n--- Test: empty pop ---" << endl;
    pop();
    pop();
    pop();                   // stack is now empty, this one must be blocked
    peek();
    display();

    // Leave some nodes in the list to show cleanup works
    push(100);
    push(200);
    display();

    releaseAll();
    cout << "\nAll remaining nodes released." << endl;
    display();

    return 0;
}
