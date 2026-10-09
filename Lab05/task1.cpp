#include <iostream>
using namespace std;

class DoublyList {
private:
	typedef struct Node {
		int data;
		Node* next;
		Node* prev;
	}*nptr;
public:
	nptr head = NULL;
	nptr tail = NULL;   // always points to the last node, so append is O(1)
	nptr curr = NULL;   // traversal helper
	nptr temp = NULL;   // used for deleting nodes
	void addNode(int value);
	void PrintForward();
	void PrintReverse();
	void ClearList();
};

// Appends a node at the end using tail
void DoublyList::addNode(int value) {
	nptr n = new Node;
	n->data = value;

	// Empty list: the new node is both head and tail
	if (head == 0) {
		head = n;
		n->prev = NULL;
		n->next = NULL;
		tail = n;
		return;
	}

	// Otherwise link the new node after the current tail
	tail->next = n;
	n->prev = tail;
	n->next = NULL;
	tail = n;
}

void DoublyList::PrintForward() {
	if (head == 0) {
		cout << "List is Empty ." << endl;
		return;
	}

	curr = head;
	cout << "Printing Forward : ";
	while (curr != 0) {   // loop on curr (not curr->next) so the last node is printed
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}

void DoublyList::PrintReverse() {
	if (head == 0) {
		cout << "List is Empty Nothing to print  ." << endl;
		return;
	}

	curr = tail;   // start from tail, no traversal needed
	cout << "Printing Reverse : ";
	while (curr != 0) {   // loop on curr so the first node is printed
		cout << curr->data << " ";
		curr = curr->prev;
	}
	cout << endl;
}

void DoublyList::ClearList() {
	if (head == 0) {
		cout << "List is Empty Nothing to Clear ." << endl;
		return;
	}

	curr = head;
	while (curr != 0) {
		temp = curr;
		curr = curr->next;   // move on before deleting, or the link is lost
		delete temp;
	}
	cout << "List cleared Successfully" << endl;

	// Reset so they don't point to deleted memory
	head = 0;
	tail = 0;
}

int main() {
	DoublyList list;
	int n;

	// Keep asking until the count is non-negative (0 is allowed)
	cout << "Enter number of elements: ";
	cin >> n;
	while (n < 0) {
		cout << "Count must be non-negative. Enter again: ";
		cin >> n;
	}

	for (int i = 0; i < n; i++) {
		int value;
		cout << "Enter value " << i + 1 << ": ";
		cin >> value;
		list.addNode(value);
	}

	list.PrintForward();
	list.PrintReverse();
	list.ClearList();   // free memory before exit

	return 0;
}