/*
 * Name         : Fahad Ali
 * Registration : 554809
 * Section      : BSCS-15D
 *
 * Lab 07 - Task 6: Implementing a deque using linked nodes
 *
 * How a deque differs from a queue (for my viva):
 *  - A queue is strictly FIFO: I insert only at the rear and delete only at
 *    the front.
 *  - A deque ("double-ended queue") lets me insert AND delete at BOTH ends,
 *    so it can behave as a queue, as a stack, or as a mix of the two.
 *  - That is why this list is doubly linked: DeleteRear() needs the node
 *    before the rear, and prev gives it to me in O(1) without traversal.
 *
 * Academic note: I wrote this program myself. The only reference I used
 * is the course text (Goodrich, Tamassia & Mount, 2011), section on deques.
 */

#include <iostream>
using namespace std;

class LinkedDeque {
private:
    // I define the node privately; the doubly linked structure needs next AND prev.
    struct node {
        int data;
        node* next;
        node* prev;
    };

    node* front;   // first node, nullptr when empty
    node* rear;    // last node, nullptr when empty

public:
    LinkedDeque() : front(nullptr), rear(nullptr) {}

    // Safety net: if I forget ClearDeque(), the destructor still frees all nodes.
    ~LinkedDeque() {
        ClearDeque();
    }

    // The deque owns raw nodes, so I forbid copying to avoid a double delete.
    LinkedDeque(const LinkedDeque&) = delete;
    LinkedDeque& operator=(const LinkedDeque&) = delete;

    bool IsEmpty() const {
        return front == nullptr;
    }

    // O(1): I use the front pointer directly and never traverse the list.
    void InsertFront(int value) {
        node* newNode = new node;
        newNode->data = value;
        newNode->prev = nullptr;          // front->prev must always be nullptr
        newNode->next = front;            // the old front (or nullptr if empty)

        if (IsEmpty()) {
            rear = newNode;               // the only node is both front and rear
        } else {
            front->prev = newNode;        // I link the old front back to the new node
        }
        front = newNode;
        cout << "Inserted " << value << " at front" << endl;
    }

    // O(1): I use the rear pointer directly and never traverse the list.
    void InsertRear(int value) {
        node* newNode = new node;
        newNode->data = value;
        newNode->next = nullptr;          // rear->next must always be nullptr
        newNode->prev = rear;             // the old rear (or nullptr if empty)

        if (IsEmpty()) {
            front = newNode;              // the only node is both front and rear
        } else {
            rear->next = newNode;         // I link the old rear forward to the new node
        }
        rear = newNode;
        cout << "Inserted " << value << " at rear" << endl;
    }

    void DeleteFront() {
        if (IsEmpty()) {
            cout << "Cannot delete from front: deque is empty." << endl;
            return;
        }
        node* temp = front;               // I keep the old front so I can delete it
        cout << "Deleted " << temp->data << " from front" << endl;

        front = front->next;
        if (front == nullptr) {
            rear = nullptr;               // I removed the only node: reset both pointers
        } else {
            front->prev = nullptr;        // the new front must not point back to freed memory
        }
        delete temp;
    }

    void DeleteRear() {
        if (IsEmpty()) {
            cout << "Cannot delete from rear: deque is empty." << endl;
            return;
        }
        node* temp = rear;                // I keep the old rear so I can delete it
        cout << "Deleted " << temp->data << " from rear" << endl;

        rear = rear->prev;                // prev lets me step back without traversal
        if (rear == nullptr) {
            front = nullptr;              // I removed the only node: reset both pointers
        } else {
            rear->next = nullptr;         // the new rear must not point forward to freed memory
        }
        delete temp;
    }

    // Front to rear, following next pointers.
    void Display() const {
        if (IsEmpty()) {
            cout << "Deque is empty." << endl;
            return;
        }
        cout << "Deque (front -> rear): ";
        for (node* current = front; current != nullptr; current = current->next) {
            cout << current->data << " ";
        }
        cout << endl;
    }

    // I added this helper to check my prev links: it walks rear to front, and it
    // must show the same values in reverse order if both link directions are correct.
    void DisplayReverse() const {
        if (IsEmpty()) {
            cout << "Deque is empty." << endl;
            return;
        }
        cout << "Deque (rear -> front): ";
        for (node* current = rear; current != nullptr; current = current->prev) {
            cout << current->data << " ";
        }
        cout << endl;
    }

    // I delete every remaining node and print each released value.
    // It stays silent if the deque is already empty.
    void ClearDeque() {
        while (front != nullptr) {
            node* temp = front;
            front = front->next;
            cout << "Released node with value " << temp->data << endl;
            delete temp;
        }
        rear = nullptr;                   // no nodes left, so rear must not dangle
    }
};

// ---------------------------------------------------------------------------
// Part A: scripted tests for every case the manual asks for.
// I use a separate LinkedDeque object for each test because copying is disabled.
// ---------------------------------------------------------------------------
void RunRequiredTests() {
    cout << "########## Part A: required test cases ##########" << endl;

    // Test 1: main scenario
    cout << "\n=== Test 1: main scenario ===" << endl;
    LinkedDeque d1;
    d1.InsertRear(20);
    d1.InsertFront(10);
    d1.InsertRear(30);
    d1.Display();          // expect 10 20 30
    d1.DisplayReverse();   // expect 30 20 10 (confirms the prev links)

    cout << "\n-- Delete from front and rear (expect 20) --" << endl;
    d1.DeleteFront();
    d1.DeleteRear();
    d1.Display();
    d1.DisplayReverse();

    cout << "\n-- Delete the remaining node, then insert again --" << endl;
    d1.DeleteFront();      // removes the only node from the front
    d1.Display();
    d1.DeleteRear();       // operation on an empty deque
    d1.DeleteFront();      // operation on an empty deque
    d1.InsertRear(40);     // inserting after the deque became empty
    d1.Display();
    d1.ClearDeque();       // I release the remaining node explicitly

    // Test 2: remove the only node from the opposite end
    cout << "\n=== Test 2: only node removed from the opposite end (rear) ===" << endl;
    LinkedDeque d2;
    d2.InsertFront(7);
    d2.Display();
    d2.DeleteRear();       // Test 1 used the front, so this one uses the rear
    d2.Display();
    d2.InsertFront(8);     // inserting again proves both pointers were reset correctly
    d2.Display();
    d2.ClearDeque();

    // Test 3: exit with nodes remaining
    cout << "\n=== Test 3: exiting with nodes remaining ===" << endl;
    LinkedDeque d3;
    d3.InsertRear(1);
    d3.InsertRear(2);
    d3.InsertFront(0);
    d3.Display();
    cout << "I now clear the deque as I would before exiting:" << endl;
    d3.ClearDeque();
    d3.Display();
}

// ---------------------------------------------------------------------------
// Part B: repeating menu for the four update operations, display and exit.
// ---------------------------------------------------------------------------
void RunMenu() {
    cout << "\n########## Part B: interactive menu ##########" << endl;

    LinkedDeque deque;
    int choice = 0;
    int value = 0;

    do {
        cout << "\n------ Deque Menu ------" << endl;
        cout << "1. Insert at front" << endl;
        cout << "2. Insert at rear" << endl;
        cout << "3. Delete from front" << endl;
        cout << "4. Delete from rear" << endl;
        cout << "5. Display" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        // If input ends (for example, end-of-file), I leave the loop instead of
        // repeating forever. The manual allows me to assume valid numeric input.
        if (!(cin >> choice)) {
            cout << "\nNo more input. Exiting." << endl;
            break;
        }

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            deque.InsertFront(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            deque.InsertRear(value);
            break;
        case 3:
            deque.DeleteFront();       // prints a message itself if the deque is empty
            break;
        case 4:
            deque.DeleteRear();        // prints a message itself if the deque is empty
            break;
        case 5:
            deque.Display();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            // A number outside 1-6 is an invalid menu choice.
            cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
        }
    } while (choice != 6);

    // I release any nodes still in the deque before the program ends.
    deque.ClearDeque();
}

int main() {
    cout << "=== Task 6: Deque using doubly linked nodes ===" << endl;
    RunRequiredTests();
    RunMenu();
    return 0;
}
