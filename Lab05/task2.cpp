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
	nptr head = nullptr;
	nptr tail = nullptr;   // always points to the last node, so append is O(1)

	void addNode(int value);
	void InsertBefore(int position, int value);
	void DeleteNode(int value);
	void PrintForward();
	void PrintReverse();
	void ClearList();
};

// Appends a node at the end using tail
void DoublyList::addNode(int value) {
	nptr n = new Node;
	n->data = value;
	n->next = nullptr;
	n->prev = tail;            // nullptr when the list is empty

	if (head == nullptr)
		head = n;
	else
		tail->next = n;
	tail = n;
}

// Inserts value before the node at the given position (positions start at 1).
// Only an existing node can be "before" target, so position 0, negative values
// and position > count are rejected and the list is left unchanged.
void DoublyList::InsertBefore(int position, int value) {
	if (position < 1) {
		cout << "Invalid position " << position << ": positions start at 1." << endl;
		return;
	}

	// Walk to the node currently at 'position'
	nptr cur = head;
	for (int i = 1; i < position && cur != nullptr; i++)
		cur = cur->next;

	if (cur == nullptr) {
		cout << "Invalid position " << position << ": no node exists there." << endl;
		return;
	}

	nptr n = new Node;
	n->data = value;
	n->next = cur;
	n->prev = cur->prev;

	if (cur->prev != nullptr)
		cur->prev->next = n;   // middle insert: previous node now points to n
	else
		head = n;              // inserting before the old head: n becomes head
	cur->prev = n;

	cout << "Inserted " << value << " before position " << position << "." << endl;
}

// Deletes only the first node holding value
void DoublyList::DeleteNode(int value) {
	if (head == nullptr) {
		cout << "List is Empty. Cannot delete " << value << "." << endl;
		return;
	}

	nptr cur = head;
	while (cur != nullptr && cur->data != value)
		cur = cur->next;

	if (cur == nullptr) {
		cout << "Value " << value << " not found. List unchanged." << endl;
		return;
	}

	// Fix the link coming into cur from the left
	if (cur->prev != nullptr)
		cur->prev->next = cur->next;
	else
		head = cur->next;      // cur was head

	// Fix the link coming into cur from the right
	if (cur->next != nullptr)
		cur->next->prev = cur->prev;
	else
		tail = cur->prev;      // cur was tail

	delete cur;
	cout << "Deleted " << value << "." << endl;
}

void DoublyList::PrintForward() {
	if (head == nullptr) {
		cout << "List is Empty." << endl;
		return;
	}
	cout << "Printing Forward : ";
	for (nptr cur = head; cur != nullptr; cur = cur->next)
		cout << cur->data << " ";
	cout << endl;
}

void DoublyList::PrintReverse() {
	if (tail == nullptr) {
		cout << "List is Empty. Nothing to print." << endl;
		return;
	}
	cout << "Printing Reverse : ";
	for (nptr cur = tail; cur != nullptr; cur = cur->prev)
		cout << cur->data << " ";
	cout << endl;
}

void DoublyList::ClearList() {
	if (head == nullptr) {
		cout << "List is Empty. Nothing to Clear." << endl;
		return;
	}
	nptr cur = head;
	while (cur != nullptr) {
		nptr nxt = cur->next;   // save the link before deleting
		delete cur;
		cur = nxt;
	}
	head = tail = nullptr;      // avoid dangling pointers
	cout << "List cleared Successfully" << endl;
}

// Prints the list in both directions
void showBoth(DoublyList& list) {
	list.PrintForward();
	list.PrintReverse();
	cout << endl;
}

int main() {
	DoublyList list;

	cout << "=== Test 1: 10 20 30, insert 15 before position 2, delete 20 ===" << endl;
	list.addNode(10);
	list.addNode(20);
	list.addNode(30);
	showBoth(list);
	list.InsertBefore(2, 15);
	showBoth(list);
	list.DeleteNode(20);
	showBoth(list);

	cout << "=== Test 2: insertion before head ===" << endl;
	list.InsertBefore(1, 5);
	showBoth(list);

	cout << "=== Test 3: invalid positions (list must not change) ===" << endl;
	list.InsertBefore(0, 99);
	list.InsertBefore(-3, 99);
	list.InsertBefore(5, 99);       // count is 4, so 5 would be "after the tail"
	list.InsertBefore(50, 99);
	showBoth(list);

	cout << "=== Test 4: delete head ===" << endl;
	list.DeleteNode(5);
	showBoth(list);

	cout << "=== Test 5: delete tail ===" << endl;
	list.DeleteNode(30);
	showBoth(list);

	cout << "=== Test 6: missing value ===" << endl;
	list.DeleteNode(99);
	showBoth(list);

	cout << "=== Test 7: delete down to the only node, then delete it ===" << endl;
	list.DeleteNode(15);
	showBoth(list);
	list.DeleteNode(10);
	showBoth(list);

	cout << "=== Test 8: operations on an empty list ===" << endl;
	list.DeleteNode(10);
	list.InsertBefore(1, 10);
	showBoth(list);

	cout << "=== Test 9: duplicates, only the first match is deleted ===" << endl;
	list.addNode(7);
	list.addNode(8);
	list.addNode(8);
	list.addNode(9);
	list.DeleteNode(8);
	showBoth(list);

	list.ClearList();
	return 0;
}
