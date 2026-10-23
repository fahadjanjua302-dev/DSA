/*
 * Name         : Fahad Ali
 * Registration : 554809
 * Section      : BSCS-15D
 *
 * Lab 07 - Task 4: Rotating service turns using a circular queue
 *
 * I reuse my CircularQueue class from Task 3 and add RotateTurn() to it.
 * I copy the class into this file because every task must compile and run
 * independently.
 *
 * Academic note: I wrote this program myself. The only reference I used
 * is the course text (Goodrich, Tamassia & Mount, 2011), section on
 * circular arrays.
 */

#include <iostream>
using namespace std;

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

    bool IsFull() const {
        return (rear + 1) % CAPACITY == front;
    }

    // I added a "verbose" flag (default true) so that RotateTurn() can reuse
    // Enqueue/Dequeue without printing extra lines for every internal step.
    // Calling Enqueue(value) still behaves exactly as it did in Task 3.
    void Enqueue(int value, bool verbose = true) {
        if (IsFull()) {
            cout << "Cannot enqueue " << value << ": queue is full." << endl;
            return;
        }
        if (IsEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % CAPACITY;
        }
        data[rear] = value;
        if (verbose) {
            cout << "Enqueued " << value << endl;
        }
    }

    void Dequeue(bool verbose = true) {
        if (IsEmpty()) {
            cout << "Cannot dequeue: queue is empty." << endl;
            return;
        }
        if (verbose) {
            cout << "Dequeued " << data[front] << endl;
        }
        if (front == rear) {
            front = -1;                        // last value removed: reset indices
            rear = -1;
        } else {
            front = (front + 1) % CAPACITY;
        }
    }

    void Peek() const {
        if (IsEmpty()) {
            cout << "Cannot peek: queue is empty." << endl;
            return;
        }
        cout << "Front value is " << data[front] << endl;
    }

    // I compute the number of stored values from the indices, so I do not need
    // an extra counter variable. This also works when rear < front.
    int Size() const {
        if (IsEmpty()) {
            return 0;
        }
        return (rear - front + CAPACITY) % CAPACITY + 1;
    }

    // I print each stored value exactly once, from front to rear, with wrap-around.
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
                break;
            }
            i = (i + 1) % CAPACITY;
        }
        cout << endl;
    }

    // One service turn: I save the front ID, remove it, and enqueue it at the
    // rear. I only use Dequeue() and Enqueue(); I never shift the array myself.
    void RotateTurn() {
        if (IsEmpty()) {
            cout << "No students are waiting, so there is no turn to give." << endl;
            return;
        }
        int servedId = data[front];   // 1) save the front ID before I remove it
        Dequeue(false);               // 2) remove it from the front
        Enqueue(servedId, false);     // 3) put it at the rear
        // Step 3 cannot fail: step 2 freed one slot, so the queue is not full.
        // With a single student this simply removes and re-adds the same ID,
        // so that student stays in the queue.

        cout << "Served ID: " << servedId << endl;
        cout << "Updated ";
        Display();
        cout << "Students in queue: " << Size() << endl;
    }
};

int main() {
    cout << "=== Task 4: Rotating service turns ===" << endl;

    // Test 1: three students and five turns in a loop.
    cout << "\n--- Test 1: students 101, 102, 103, five turns ---" << endl;
    CircularQueue lab;
    lab.Enqueue(101);
    lab.Enqueue(102);
    lab.Enqueue(103);
    cout << "Initial ";
    lab.Display();
    cout << "Students in queue: " << lab.Size() << endl;

    for (int turn = 1; turn <= 5; turn++) {
        cout << "\nTurn " << turn << ":" << endl;
        lab.RotateTurn();
        // After turn 1 I expect 102 103 101; after turn 2 I expect 103 101 102.
    }

    // Test 2: nobody is waiting.
    cout << "\n--- Test 2: empty queue ---" << endl;
    CircularQueue emptyLab;
    emptyLab.RotateTurn();

    // Test 3: exactly one student must remain after a turn.
    cout << "\n--- Test 3: queue with one student ---" << endl;
    CircularQueue singleLab;
    singleLab.Enqueue(201);
    singleLab.RotateTurn();
    singleLab.RotateTurn();

    return 0;
}
