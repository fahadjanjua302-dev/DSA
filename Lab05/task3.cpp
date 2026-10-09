#include <iostream>
using namespace std;

// Singly circular linked list: the last node points back to the first node.
// We keep tail, and tail->next is always head.
class CircularList {
private:
	typedef struct Node {
		int data;
		Node* next;
	}*nptr;
public:
	nptr head = nullptr;
	nptr tail = nullptr;

	void AddNode(int value);
	void PrintList();
	int CountNodes();
	void ClearList();
};

// Appends at the end using tail and keeps tail->next = head
void CircularList::AddNode(int value) {
	nptr n = new Node;
	n->data = value;

	if (head == nullptr) {
		head = tail = n;
		n->next = n;        // a single node points to itself
		return;
	}

	n->next = head;         // new last node points back to head
	tail->next = n;         // old last node points to the new node
	tail = n;
}

// Prints every value exactly once.
// do-while is used so a one-node list is still printed, and the loop stops
// when we come back to head (one complete cycle), never at nullptr.
void CircularList::PrintList() {
	if (head == nullptr) {
		cout << "List is Empty." << endl;
		return;
	}

	cout << "List : ";
	nptr cur = head;
	do {
		cout << cur->data << " ";
		cur = cur->next;
	} while (cur != head);
	cout << endl;
}

// Counts nodes by going around the cycle once
int CircularList::CountNodes() {
	if (head == nullptr)
		return 0;

	int count = 0;
	nptr cur = head;
	do {
		count++;
		cur = cur->next;
	} while (cur != head);
	return count;
}

// Deletes every node and resets the list to empty
void CircularList::ClearList() {
	if (head == nullptr) {
		cout << "List is Empty. Nothing to Clear." << endl;
		return;
	}

	tail->next = nullptr;       // break the cycle so a normal traversal can stop
	nptr cur = head;
	while (cur != nullptr) {
		nptr nxt = cur->next;   // save the link before deleting
		delete cur;
		cur = nxt;
	}
	head = tail = nullptr;
	cout << "List cleared Successfully" << endl;
}

int main() {
	cout << "=== Test 1: empty list ===" << endl;
	CircularList empty;
	empty.PrintList();
	cout << "Count: " << empty.CountNodes() << endl << endl;

	cout << "=== Test 2: one node ===" << endl;
	CircularList one;
	one.AddNode(5);
	one.PrintList();
	cout << "Count: " << one.CountNodes() << endl;
	one.ClearList();
	cout << endl;

	cout << "=== Test 3: 10, 20, 30 ===" << endl;
	CircularList three;
	three.AddNode(10);
	three.AddNode(20);
	three.AddNode(30);
	three.PrintList();
	cout << "Count: " << three.CountNodes() << endl;
	three.ClearList();
	cout << endl;

	cout << "=== Why nullptr-based traversal does not terminate ===" << endl;
	cout << "In a non-empty circular list no node has next == nullptr:\n"
	        "the last node points back to head. A loop such as\n"
	        "    while (cur != nullptr) cur = cur->next;\n"
	        "therefore never sees nullptr and keeps going around the cycle forever.\n"
	        "We must stop when cur returns to head instead." << endl;

	return 0;
}
