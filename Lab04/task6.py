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

    // Destructor ensures all memory is deallocated when program exits or object is destroyed
    ~List() {
        ClearList();
    }

    // 1. Insert at Beginning
    void InsertAtBeginning(int addData) {
        nptr n = new Node;
        n->data = addData;
        n->next = head;
        head = n;
        cout << "Inserted " << addData << " at the beginning." << endl;
    }

    // 2. Insert at End
    void AddNode(int addData) {
        nptr n = new Node;
        n->data = addData;
        n->next = nullptr;

        if (head == nullptr) {
            head = n;
            cout << "Inserted " << addData << " at the end." << endl;
            return;
        }

        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = n;
        cout << "Inserted " << addData << " at the end." << endl;
    }

    // 3. Search by Value
    void SearchNode(int searchData) {
        curr = head;
        int position = 1;

        while (curr != nullptr) {
            if (curr->data == searchData) {
                cout << "Value " << searchData << " found at position " << position << "." << endl;
                return;
            }
            curr = curr->next;
            position++;
        }

        cout << "Value not found" << endl;
    }

    // 4. Delete by Value
    void DeleteNode(int delData) {
        if (head == nullptr) {
            cout << "Cannot delete " << delData << ": List is empty." << endl;
            return;
        }

        // Delete first node
        if (head->data == delData) {
            temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
            cout << "Deleted " << delData << "." << endl;
            return;
        }

        // Delete middle or last node
        temp = head;
        curr = head->next;

        while (curr != nullptr) {
            if (curr->data == delData) {
                temp->next = curr->next;
                delete curr;
                curr = nullptr;
                cout << "Deleted " << delData << "." << endl;
                return;
            }
            temp = curr;
            curr = curr->next;
        }

        cout << "Value " << delData << " not found in list." << endl;
    }

    // 5. Display All Nodes
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

    // 6. Count Nodes
    int CountNodes() {
        curr = head;
        int count = 0;
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // 7. Display Second Node
    void PrintSecondNode() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Fewer than two nodes exist." << endl;
            return;
        }
        cout << "Second node: " << head->next->data << endl;
    }

    // Deallocates all nodes and resets head
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
    int choice = 0;
    int val = 0;

    do {
        cout << "\n=================================" << endl;
        cout << "       LINKED LIST MENU          " << endl;
        cout << "=================================" << endl;
        cout << "1. Insert at Beginning" << endl;
        cout << "2. Insert at End" << endl;
        cout << "3. Search by Value" << endl;
        cout << "4. Delete by Value" << endl;
        cout << "5. Display All Nodes" << endl;
        cout << "6. Count Nodes" << endl;
        cout << "7. Display Second Node" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        cout << endl;

        switch (choice) {
        case 1:
            cout << "Enter value to insert at beginning: ";
            cin >> val;
            l.InsertAtBeginning(val);
            break;
        case 2:
            cout << "Enter value to insert at end: ";
            cin >> val;
            l.AddNode(val);
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> val;
            l.SearchNode(val);
            break;
        case 4:
            cout << "Enter value to delete: ";
            cin >> val;
            l.DeleteNode(val);
            break;
        case 5:
            l.PrintList();
            break;
        case 6:
            cout << "Total number of nodes: " << l.CountNodes() << endl;
            break;
        case 7:
            l.PrintSecondNode();
            break;
        case 8:
            l.ClearList(); // Releasing remaining nodes before exiting
            cout << "Exiting application. Memory cleared!" << endl;
            break;
        default:
            cout << "Invalid menu choice! Please try again." << endl;
            break;
        }
    } while (choice != 8);

    return 0;
}