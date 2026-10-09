#include <iostream>
#include <limits>
using namespace std;

class LinkedStack {
private:
	typedef struct Node {
		int data;
		Node* next;
	}*nptr;
	nptr top = nullptr;          // top of the stack = head of the list
public:
	bool IsEmpty();

	void Push(int value);
	void Pop();
	void Peek();
	void Display();
	void ClearStack();

	~LinkedStack();
};

bool LinkedStack::IsEmpty() {
	return top == nullptr;
}

// Frees any nodes still in the stack
LinkedStack::~LinkedStack() {
	ClearStack();
}

// O(1): the new node becomes the head
void LinkedStack::Push(int value) {
	nptr n = new Node;
	n->data = value;
	n->next = top;
	top = n;
	cout << "Pushed " << value << "." << endl;
}

// O(1): remove the head node
void LinkedStack::Pop() {
	if (IsEmpty()) {
		cout << "Underflow: stack is empty, nothing to pop." << endl;
		return;
	}
	nptr old = top;
	top = top->next;             // move top down before deleting
	cout << "Popped " << old->data << "." << endl;
	delete old;                  // release the popped node
}

void LinkedStack::Peek() {
	if (IsEmpty()) {
		cout << "Underflow: stack is empty, nothing to peek." << endl;
		return;
	}
	cout << "Top is " << top->data << "." << endl;
}

// Displays from top to bottom
void LinkedStack::Display() {
	if (IsEmpty()) {
		cout << "Stack is empty." << endl;
		return;
	}
	cout << "Stack (top to bottom) : ";
	for (nptr cur = top; cur != nullptr; cur = cur->next)
		cout << cur->data << " ";
	cout << endl;
}

// Releases every remaining node
void LinkedStack::ClearStack() {
	while (top != nullptr) {
		nptr nxt = top->next;
		delete top;
		top = nxt;
	}
}

// Reads an int; returns false on bad input (e.g. a letter) and clears the error
bool readInt(int& out) {
	if (cin >> out)
		return true;
	if (cin.eof())
		return false;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return false;
}

int main() {
	LinkedStack s;
	int choice = 0;

	do {
		cout << endl;
		cout << "===== Linked Stack Menu =====" << endl;
		cout << "1. Push" << endl;
		cout << "2. Pop" << endl;
		cout << "3. Peek" << endl;
		cout << "4. Display" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter choice: ";

		if (!readInt(choice)) {
			if (cin.eof())
				break;           // input ended, leave the loop
			cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
			choice = 0;
			continue;
		}

		switch (choice) {
		case 1: {
			int value;
			cout << "Enter value to push: ";
			if (readInt(value))
				s.Push(value);
			else
				cout << "Invalid value. Nothing pushed." << endl;
			break;
		}
		case 2:
			s.Pop();
			break;
		case 3:
			s.Peek();
			break;
		case 4:
			s.Display();
			break;
		case 5:
			cout << "Exiting. Releasing remaining nodes..." << endl;
			break;
		default:
			cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
		}
	} while (choice != 5);

	s.ClearStack();              // release remaining nodes before exit
	return 0;
}

/*
LIFO (Last In, First Out):
  The most recently pushed item is the first one removed. Push and pop both
  work only at the top, like a pile of plates: you add and take from the top.
  Here 10, 20, 30 are pushed, so 30 comes out first, then 20, then 10.

Task 5 (array) vs Task 6 (linked nodes):
  - ArrayStack has a fixed capacity of 5. The sixth push must be rejected
    (overflow), because the array cannot grow.
  - LinkedStack allocates one node per push with new, so it grows until memory
    runs out and has no fixed limit. The cost is extra memory per item for the
    next pointer, and every popped node must be deleted explicitly.
  - Both give O(1) push and pop.
*/
