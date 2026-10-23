/*
 * Name         : Fahad Ali
 * Registration : 554809
 * Section      : BSCS-15D
 *
 * Lab 07 - Task 1: Implementing a linear queue using an array
 *
 * Academic note: I wrote this program myself. The only reference I used
 * is the course text (Goodrich, Tamassia & Mount, 2011), section on queues.
 */

#include <iostream>
using namespace std;

// I keep the capacity in one constant so the "full" check and the array size
// can never disagree with each other.
const int CAPACITY = 5;

class ArrayQueue {
private:
    int data[CAPACITY];  // I store the queue values here
    int front;           // index of the first value, -1 when the queue is empty
    int rear;            // index of the last value, -1 when the queue is empty

public:
    // I start with front = rear = -1, which is how I represent an empty queue.
    ArrayQueue() : front(-1), rear(-1) {}

    // The queue is empty exactly when front is -1.
    bool IsEmpty() const {
        return front == -1;
    }

    // In a LINEAR queue I never reuse freed slots, so the queue is full as soon
    // as rear reaches the last index (4), even if earlier slots are unused.
    bool IsFull() const {
        return rear == CAPACITY - 1;
    }

    // I insert at the rear. No shifting is needed.
    void Enqueue(int value) {
        if (IsFull()) {
            // I reject the insertion and leave front, rear and data untouched.
            cout << "Cannot enqueue " << value
                 << ": queue is full (rear is at the last index)." << endl;
            return;
        }
        if (IsEmpty()) {
            front = 0;   // the first value goes to index 0, so front must follow it
        }
        rear++;          // when empty, rear moves from -1 to 0
        data[rear] = value;
        cout << "Enqueued " << value << endl;
    }

    // I remove from the front by only moving the front index; I never shift elements.
    void Dequeue() {
        if (IsEmpty()) {
            cout << "Cannot dequeue: queue is empty." << endl;
            return;
        }
        cout << "Dequeued " << data[front] << endl;

        if (front == rear) {
            // I just removed the last remaining value, so I reset both indices
            // to -1. This is what lets the array be reused from index 0 again.
            front = -1;
            rear = -1;
        } else {
            front++;
        }
    }

    // I only display the front value; nothing is removed.
    void Peek() const {
        if (IsEmpty()) {
            cout << "Cannot peek: queue is empty." << endl;
            return;
        }
        cout << "Front value is " << data[front] << endl;
    }

    // I print from front to rear. I also print the indices so the behaviour
    // of the linear queue (front moving forward, rear stuck at 4) is visible.
    void Display() const {
        if (IsEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue (front -> rear): ";
        for (int i = front; i <= rear; i++) {
            cout << data[i] << " ";
        }
        cout << "  [front = " << front << ", rear = " << rear << "]" << endl;
    }
};

int main() {
    ArrayQueue q;

    cout << "=== Task 1: Linear queue using an array ===" << endl;

    cout << "\n--- Step 1: enqueue 10, 20, 30, 40, 50 ---" << endl;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Enqueue(40);
    q.Enqueue(50);
    q.Display();

    cout << "\n--- Step 2: dequeue twice ---" << endl;
    q.Dequeue();
    q.Dequeue();

    cout << "\n--- Step 3: try to enqueue 60 (must be rejected) ---" << endl;
    // Indices 0 and 1 are free, but a linear queue cannot reuse them.
    q.Enqueue(60);

    cout << "\n--- Step 4: display and peek (expect 30, 40, 50) ---" << endl;
    q.Display();
    q.Peek();

    cout << "\n--- Step 5: empty the queue ---" << endl;
    q.Dequeue();   // 30
    q.Dequeue();   // 40
    q.Dequeue();   // 50 -> indices reset to -1 here
    q.Display();

    cout << "\n--- Step 6: dequeue and peek on an empty queue ---" << endl;
    q.Dequeue();
    q.Peek();

    cout << "\n--- Step 7: enqueue 70 (indices were reset, so reuse works) ---" << endl;
    q.Enqueue(70);
    q.Display();   // expect front = 0, rear = 0
    q.Peek();

    return 0;
}
