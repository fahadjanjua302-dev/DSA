#include <iostream>
using namespace std;

class List {
private:
    typedef struct Node {
        int data;
        Node* next;
    }*nptr;

public:
    nptr head = NULL;
    nptr curr = NULL;
    nptr temp = NULL;

    // Destructor to prevent memory leaks when object goes out of scope
    ~List() {
        ClearList();
    }

    void CreateThreeNodes() {
        int arr[3] = { 0 };

        cout << "Enter the 3 input numbers." << endl;
        for (int i = 1; i < 4; i++) {
            cout << i << ". ";
            cin >> arr[i - 1];
        }

        if (head == 0) {
            nptr n = new Node;
            n->data = arr[0];
            head = n;
            curr = n;
            for (int i = 1; i < 3; i++) {
                nptr f = new Node;
                curr->next = f;
                f->data = arr[i];
                curr = f;
            }
            curr->next = 0;
            return;
        }

        curr = head;
        while (curr->next != 0) {
            curr = curr->next;
        }

        for (int i = 0; i < 3; i++) {
            nptr f = new Node;
            curr->next = f;
            f->data = arr[i];
            curr = f;
        }
        curr->next = 0;
    }

    void PrintList() {
        if (head == 0) {
            cout << "List is empty, nothing to print." << endl;
            return;
        }
        curr = head;
        cout << "List elements : ";
        while (curr != 0) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void ClearList() {
        if (head == 0) {
            cout << "List already empty." << endl;
            return;
        }
        curr = head;
        while (curr != NULL) {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
        head = NULL; 
        temp = NULL;
    }
};

int main() {
    List l;
    l.CreateThreeNodes();
    l.PrintList();
    l.ClearList();
    l.PrintList(); 
}