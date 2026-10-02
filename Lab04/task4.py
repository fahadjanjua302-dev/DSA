#include <iostream>
using namespace std;

class List {
private:
    typedef struct Node {
        int data;
        Node* next;
    }*nptr;

public:
    nptr head = nullptr;
    nptr curr = nullptr;
    nptr temp = nullptr;

    ~List() {
        ClearList();
    }

    // Inserts a new node at the head of the list
    void InsertAtBeginning(int addData) {
        nptr n = new Node;
        n->data = addData;
        n->next = head; // Point new node to the current first node
        head = n;       // Update head to point to the new node
    }

    // Inserts a new node at the end of the list
    void AddNode(int addData) {
        nptr n = new Node;
        n->data = addData;
        n->next = nullptr;

        if (head == nullptr) {
            head = n;
            return;
        }

        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
    }

    // Displays the contents of the list
    void PrintList() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        curr = head;
        cout << "List elements: ";
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // Frees all allocated memory
    void ClearList() {
        curr = head;
        while (curr != nullptr) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = nullptr;
    }
};

int main() {
    List l;

    cout << "1. Insert 20 at beginning:" << endl;
    l.InsertAtBeginning(20);
    l.PrintList();

    cout << "\n2. Insert 10 at beginning:" << endl;
    l.InsertAtBeginning(10);
    l.PrintList();

    cout << "\n3. Append 30 at end:" << endl;
    l.AddNode(30);
    l.PrintList();

    cout << "\nList cleared :" << endl;
    l.ClearList();

    return 0;
}