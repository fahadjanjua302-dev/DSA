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

    // Displays the 1-based position of the first matching value
    void SearchNode(int searchData) {
        curr = head;
        int position = 1;

        while (curr != nullptr) {
            if (curr->data == searchData) {
                cout << "Value " << searchData << " found at position " << position << endl;
                return;
            }
            curr = curr->next;
            position++;
        }

        cout << "Value not found" << endl;
    }

    // Displays only the second node if it exists
    void PrintSecondNode() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Fewer than two nodes exist." << endl;
            return;
        }
        cout << "Second node: " << head->next->data << endl;
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
    // 1. Test Empty List
    cout << "=== 1. Testing Empty List ===" << endl;
    List l1;
    l1.PrintList();
    l1.PrintSecondNode();
    l1.SearchNode(20);

    // 2. Test One-Node List
    cout << "\n=== 2. Testing One-Node List ===" << endl;
    List l2;
    l2.AddNode(10);
    l2.PrintList();
    l2.PrintSecondNode();
    l2.SearchNode(10);

    // 3. Test List [10, 20, 30, 20]
    cout << "\n=== 3. Testing Four-Node List [10, 20, 30, 20] ===" << endl;
    List l3;
    l3.AddNode(10);
    l3.AddNode(20);
    l3.AddNode(30);
    l3.AddNode(20);

    l3.PrintList();
    l3.PrintSecondNode(); // Should print 20

    cout << "\nSearch Queries:" << endl;
    l3.SearchNode(20); // First match is at position 2
    l3.SearchNode(99); // Should print "Value not found"

    return 0;
}