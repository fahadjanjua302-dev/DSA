#include <iostream>
using namespace std;

// Circular linked list with deletion
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
	void DeleteNode(int value);
	void ClearList();
};

void CircularList::AddNode(int value) {
	nptr n = new Node;
	n->data = value;

	if (head == nullptr) {
		head = tail = n;
		n->next = n;        // a single node points to itself
		return;
	}

	n->next = head;
	tail->next = n;
	tail = n;
}

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

// Deletes the first node holding value.
// The search stops after one full cycle if the value is absent.
void CircularList::DeleteNode(int value) {
	if (head == nullptr) {
		cout << "List is Empty. Cannot delete " << value << "." << endl;
		return;
	}

	// prev always trails cur by one node; it starts at tail because
	// tail is the node "before" head in the cycle
	nptr prev = tail;
	nptr cur = head;
	bool found = false;
	do {
		if (cur->data == value) {
			found = true;
			break;
		}
		prev = cur;
		cur = cur->next;
	} while (cur != head);          // one complete cycle only

	if (!found) {
		cout << "Value " << value << " not found. List unchanged." << endl;
		return;
	}

	if (cur == head && cur == tail) {
		// Only node: the list becomes empty
		head = tail = nullptr;
	} else {
		prev->next = cur->next;     // bypass cur
		if (cur == head)
			head = cur->next;       // prev is tail, so tail->next now points to the new head
		if (cur == tail)
			tail = prev;            // prev->next already points to head
	}

	delete cur;
	cout << "Deleted " << value << "." << endl;
}

void CircularList::ClearList() {
	if (head == nullptr) {
		cout << "List is Empty. Nothing to Clear." << endl;
		return;
	}

	tail->next = nullptr;           // break the cycle so a normal traversal can stop
	nptr cur = head;
	while (cur != nullptr) {
		nptr nxt = cur->next;
		delete cur;
		cur = nxt;
	}
	head = tail = nullptr;
	cout << "List cleared Successfully" << endl;
}

// Shows the list and its count after every operation
void show(CircularList& list) {
	list.PrintList();
	cout << "Count: " << list.CountNodes() << endl << endl;
}

int main() {
	CircularList list;

	cout << "=== Test 1: delete on an empty list ===" << endl;
	list.DeleteNode(10);
	show(list);

	cout << "=== Test 2: 10, 20, 30 ===" << endl;
	list.AddNode(10);
	list.AddNode(20);
	list.AddNode(30);
	show(list);

	cout << "=== Test 3: missing value ===" << endl;
	list.DeleteNode(99);
	show(list);

	cout << "=== Test 4: delete head (10) ===" << endl;
	list.DeleteNode(10);
	show(list);

	cout << "=== Test 5: delete tail (30) ===" << endl;
	list.DeleteNode(30);
	show(list);

	cout << "=== Test 6: delete the only node (20) ===" << endl;
	list.DeleteNode(20);
	show(list);
	cout << "head is " << (list.head == nullptr ? "nullptr" : "NOT nullptr")
	     << ", tail is " << (list.tail == nullptr ? "nullptr" : "NOT nullptr") << endl << endl;

	cout << "=== Test 7: delete a middle node ===" << endl;
	list.AddNode(1);
	list.AddNode(2);
	list.AddNode(3);
	list.DeleteNode(2);
	show(list);
	list.ClearList();
	cout << endl;

	cout << "=== Test 8: duplicates, delete 20 once from 10 20 20 30 ===" << endl;
	list.AddNode(10);
	list.AddNode(20);
	list.AddNode(20);
	list.AddNode(30);
	list.DeleteNode(20);
	show(list);

	list.ClearList();
	return 0;
}
