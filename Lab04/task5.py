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

    void DeleteNode(int delData) {
        // Case 1: Empty List
        if (head == nullptr) {
            cout << "Cannot delete " << delData << ": List is empty." << endl;
            return;
        }

        // Case 2: Deleting First Node
        if (head->data == delData) {
            temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
            cout << "Deleted " << delData << endl;
            return;
        }

        // Case 3: Deleting Middle or Last Node using two pointers
        temp = head;
        curr = head->next;

        while (curr != nullptr) {
            if (curr->data == delData) {
                temp->next = curr->next;
                delete curr;
                curr = nullptr;
                cout << "Deleted " << delData << endl;
                return;
            }
            temp = curr;
            curr = curr->next;
        }

        // Case 4: Value Not Found
        cout << "Value " << delData << " not found in list." << endl;
    }

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

    cout << "=== 1. Test Deleting from Empty List ===" << endl;
    l.DeleteNode(10);
    l.PrintList();

    cout << "\n=== 2. Test Deleting the Only Node ===" << endl;
    l.AddNode(50);
    l.PrintList();
    l.DeleteNode(50);
    l.PrintList();

    cout << "\n=== 3. Setup List: [10, 20, 20, 30] ===" << endl;
    l.AddNode(10);
    l.AddNode(20);
    l.AddNode(20);
    l.AddNode(30);
    l.PrintList();

    cout << "\n--- Test A: Delete duplicate 20 (Middle Node / First Match) ---" << endl;
    l.DeleteNode(20);
    l.PrintList(); // Output must be: 10 20 30

    cout << "\n--- Test B: Delete Missing Value (99) ---" << endl;
    l.DeleteNode(99);
    l.PrintList();

    cout << "\n--- Test C: Delete First Node (10) ---" << endl;
    l.DeleteNode(10);
    l.PrintList();

    cout << "\n--- Test D: Delete Last Node (30) ---" << endl;
    l.DeleteNode(30);
    l.PrintList();

    cout << "\n--- Test E: Delete Remaining Node (20) ---" << endl;
    l.DeleteNode(20);
    l.PrintList();

    return 0;
}