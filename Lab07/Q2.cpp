/*
 * Name         : Fahad Ali
 * Registration : 554809
 * Section      : BSCS-15D
 *
 * Lab 07 - Task 2: Implementing a queue using linked nodes
 *
 * Academic note: I wrote this program myself. The only reference I used
 * is the course text (Goodrich, Tamassia & Mount, 2011), section on queues.
 */

#include <iostream>
using namespace std;

class LinkedQueue {
private:
    // I define the node privately. A queue only moves forward, so I omit prev.
    struct node {
        int data;
        node* next;
    };

    node* front;   // first node (next to be removed), nullptr when empty
    node* rear;    // last node (most recent insertion), nullptr when empty

public:
    LinkedQueue() : front(nullptr), rear(nullptr) {}

    // I release any remaining nodes automatically as a safety net.
    // I still call ClearQueue() myself in main() before exiting, as required.
    ~LinkedQueue() {
        ClearQueue();
    }

    // The queue owns raw nodes, so I forbid copying. A copy would share the
    // same nodes and cause a double delete.
    LinkedQueue(const LinkedQueue&) = delete;
    LinkedQueue& operator=(const LinkedQueue&) = delete;

    bool IsEmpty() const {
        return front == nullptr;
    }

    // I insert at the rear using the rear pointer, so I never traverse the list.
    void Enqueue(int value) {
        node* newNode = new node;
        newNode->data = value;
        newNode->next = nullptr;      // the new node is the last one

        if (IsEmpty()) {
            // The queue was empty, so this node is both the front and the rear.
            front = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;     // link the old last node to the new one
            rear = newNode;           // then move rear to the new node
        }
        cout << "Enqueued " << value << endl;
    }

    // I remove from the front using the front pointer, so I never traverse the list.
    void Dequeue() {
        if (IsEmpty()) {
            cout << "Cannot dequeue: queue is empty." << endl;
            return;
        }
        node* temp = front;           // I keep the old front so I can delete it
        cout << "Dequeued " << temp->data << endl;

        front = front->next;          // I move front forward first
        if (front == nullptr) {
            // I just removed the last node. If I did not reset rear here, it
            // would be left pointing at deleted memory (a dangling pointer).
            rear = nullptr;
        }
        delete temp;                  // I free the removed node
    }

    void Peek() const {
        if (IsEmpty()) {
            cout << "Cannot peek: queue is empty." << endl;
            return;
        }
        cout << "Front value is " << front->data << endl;
    }

    // I print from front to rear by following the next pointers.
    void Display() const {
        if (IsEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue (front -> rear): ";
        for (node* current = front; current != nullptr; current = current->next) {
            cout << current->data << " ";
        }
        cout << endl;
    }

    // I delete every remaining node, printing each value as it is released.
    // I stay silent when the queue is already empty so the destructor does not
    // print anything extra after I have already cleared it.
    void ClearQueue() {
        while (front != nullptr) {
            node* temp = front;
            front = front->next;
            cout << "Released node with value " << temp->data << endl;
            delete temp;
        }
        rear = nullptr;   // the queue is empty, so rear must not point anywhere
    }
};

int main() {
    LinkedQueue q;

    cout << "=== Task 2: Queue using linked nodes ===" << endl;

    cout << "\n--- Step 1: enqueue 10, 20, 30 ---" << endl;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Display();

    cout << "\n--- Step 2: dequeue once, then display and peek (expect 20, 30) ---" << endl;
    q.Dequeue();
    q.Display();
    q.Peek();

    cout << "\n--- Step 3: empty the queue, then test an empty queue ---" << endl;
    q.Dequeue();   // 20
    q.Dequeue();   // 30 -> last node, rear is reset to nullptr
    q.Display();
    q.Dequeue();   // dequeue on empty
    q.Peek();      // peek on empty

    cout << "\n--- Step 4: removal of the only node ---" << endl;
    q.Enqueue(40);
    q.Display();
    q.Dequeue();   // removes the single node; front and rear both become nullptr
    q.Display();

    cout << "\n--- Step 5: insertion after the queue became empty ---" << endl;
    q.Enqueue(50);
    q.Enqueue(60);   // this only works safely because rear was reset earlier
    q.Display();
    q.Peek();

    cout << "\n--- Step 6: release all remaining nodes before exit ---" << endl;
    q.ClearQueue();
    q.Display();

    return 0;
}
