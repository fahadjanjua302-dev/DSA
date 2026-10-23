/*
 * Name         : Fahad Ali
 * Registration : 554809
 * Section      : BSCS-15D
 *
 * Lab 07 - Task 3: Implementing a circular queue
 *
 * Academic note: I wrote this program myself. The only reference I used
 * is the course text (Goodrich, Tamassia & Mount, 2011), section on
 * circular arrays.
 */

#include <iostream>
using namespace std;

// I use one constant for the capacity; every wrap-around uses % CAPACITY (= % 5).
const int CAPACITY = 5;

class CircularQueue {
private:
    int data[CAPACITY];
    int front;   // index of the first value, -1 when empty
    int rear;    // index of the last value, -1 when empty

public:
    CircularQueue() : front(-1), rear(-1) {}

    bool IsEmpty() const {
        return front == -1;
    }

    // Full condition from the manual: the slot after rear (with wrap-around)
    // is the front. When the queue is empty, front is -1 and (rear + 1) % 5
    // can never equal -1, so an empty queue is never reported as full.
    bool IsFull() const {
        return (rear + 1) % CAPACITY == front;
    }

    void Enqueue(int value) {
        if (IsFull()) {
            cout << "Cannot enqueue " << value << ": queue is full." << endl;
            return;
        }
        if (IsEmpty()) {
            front = 0;
            rear = 0;                          // first value goes to index 0
        } else {
            rear = (rear + 1) % CAPACITY;      // I wrap around instead of shifting
        }
        data[rear] = value;
        cout << "Enqueued " << value << endl;
    }

    void Dequeue() {
        if (IsEmpty()) {
            cout << "Cannot dequeue: queue is empty." << endl;
            return;
        }
        cout << "Dequeued " << data[front] << endl;

        if (front == rear) {
            // That was the last stored value, so I reset both indices to -1.
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % CAPACITY;    // the freed slot becomes reusable
        }
    }

    void Peek() const {
        if (IsEmpty()) {
            cout << "Cannot peek: queue is empty." << endl;
            return;
        }
        cout << "Front value is " << data[front] << endl;
    }

    // I walk from front to rear with wrap-around. I stop when I have printed the
    // value at rear, so every stored value appears exactly once. A simple
    // "for (i = front; i <= rear; i++)" would be wrong when rear < front.
    void Display() const {
        if (IsEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Queue (front -> rear): ";
        int i = front;
        while (true) {
            cout << data[i] << " ";
            if (i == rear) {
                break;                         // I have printed the last value
            }
            i = (i + 1) % CAPACITY;
        }
        cout << "  [front = " << front << ", rear = " << rear << "]" << endl;
    }
};

int main() {
    CircularQueue q;

    cout << "=== Task 3: Circular queue ===" << endl;

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
    q.Display();

    cout << "\n--- Step 3: enqueue 60 and 70 (they wrap to indices 0 and 1) ---" << endl;
    q.Enqueue(60);
    q.Enqueue(70);
    q.Display();   // expect 30 40 50 60 70 with front = 2, rear = 1 (rear < front)

    cout << "\n--- Step 4: another insertion must be rejected ---" << endl;
    q.Enqueue(80);
    q.Display();

    cout << "\n--- Step 5: empty the queue, then dequeue once more ---" << endl;
    q.Dequeue();   // 30
    q.Dequeue();   // 40
    q.Dequeue();   // 50
    q.Dequeue();   // 60
    q.Dequeue();   // 70 -> indices reset to -1
    q.Display();
    q.Dequeue();   // dequeue on empty
    q.Peek();      // peek on empty

    cout << "\n--- Step 6: insertion into an empty queue again ---" << endl;
    q.Enqueue(90);
    q.Display();   // expect front = 0, rear = 0
    q.Peek();

    return 0;
}
