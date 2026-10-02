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

    
    int CountNodes() {
        curr = head;
        int count = 0;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
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
    // Testing with n = 0, n = 1, and n = 5
    int testCases[3] = {0, 1, 5};

    for (int t = 0; t < 3; t++) {
        List l;
        int n = testCases[t];

        cout << "===========================" << endl;
        cout << "Testing for n = " << n << endl;

        for (int i = 0; i < n; i++) {
            int val;
            cout << "Enter integer " << (i + 1) << ": ";
            cin >> val;
            l.AddNode(val);
        }

        l.PrintList();
        cout << "Node Count: " << l.CountNodes() << endl;
    }

    return 0;
}