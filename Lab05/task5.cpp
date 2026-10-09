#include <iostream>
using namespace std;

class ArrayStack {
private:
	static const int SIZE = 5;   // fixed capacity
	int items[SIZE];
	int top;                     // index of the top item, -1 when empty
public:
	ArrayStack();

	bool IsEmpty();
	bool IsFull();

	void Push(int value);
	void Pop();
	void Peek();
	void Display();
};

// Starts with an empty stack
ArrayStack::ArrayStack() : top(-1) {}

bool ArrayStack::IsEmpty() {
	return top == -1;
}

bool ArrayStack::IsFull() {
	return top == SIZE - 1;
}

void ArrayStack::Push(int value) {
	if (IsFull()) {
		cout << "Overflow: stack is full, cannot push " << value << "." << endl;
		return;
	}
	items[++top] = value;        // move top up first, then store
	cout << "Pushed " << value << "." << endl;
}

void ArrayStack::Pop() {
	if (IsEmpty()) {
		cout << "Underflow: stack is empty, nothing to pop." << endl;
		return;
	}
	cout << "Popped " << items[top] << "." << endl;
	top--;                       // the old value stays in the array but is no longer part of the stack
}

void ArrayStack::Peek() {
	if (IsEmpty()) {
		cout << "Underflow: stack is empty, nothing to peek." << endl;
		return;
	}
	cout << "Top is " << items[top] << "." << endl;
}

// Displays from top to bottom
void ArrayStack::Display() {
	if (IsEmpty()) {
		cout << "Stack is empty." << endl;
		return;
	}
	cout << "Stack (top to bottom) : ";
	for (int i = top; i >= 0; i--)
		cout << items[i] << " ";
	cout << endl;
}

int main() {
	ArrayStack s;

	cout << "=== Push 10, 20, 30, 40, 50 ===" << endl;
	s.Push(10);
	s.Push(20);
	s.Push(30);
	s.Push(40);
	s.Push(50);
	s.Display();

	cout << endl << "=== Sixth push is rejected ===" << endl;
	s.Push(60);
	s.Display();

	cout << endl << "=== Pop 50, then peek 40 ===" << endl;
	s.Pop();
	s.Peek();

	cout << endl << "=== Empty the stack ===" << endl;
	while (!s.IsEmpty())
		s.Pop();
	s.Display();

	cout << endl << "=== One further pop and peek on the empty stack ===" << endl;
	s.Pop();
	s.Peek();

	return 0;
}
