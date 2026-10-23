/*
 * Name         : Fahad Ali
 * Registration : 554809
 * Section      : BSCS-15D
 *
 * Lab 07 - Task 5: Implementing a deque using a circular array
 *
 * Academic note: I wrote this program myself. The only reference I used
 * is the course text (Goodrich, Tamassia & Mount, 2011), section on deques.
 */

#include <iostream>
using namespace std;

// All wrap-around arithmetic below uses this capacity (5 in the manual).
const int CAPACITY = 5;

class ArrayDeque {
private:
    int data[CAPACITY];
    int front;   // index of the first value, -1 when empty
    int rear;    // index of the last value, -1 when empty

public:
    ArrayDeque() : front(-1), rear(-1) {}

    bool IsEmpty() const {
        return front == -1;
    }

    // Same full rule as the circular queue: the slot after rear is the front.
    bool IsFull() const {
        return (rear + 1) % CAPACITY == front;
    }

    // Inserting at the front means moving front one step BACKWARD (with wrap).
    // I add CAPACITY before the modulo so the result never becomes negative.
    void InsertFront(int value) {
        if (IsFull()) {
            cout << "Cannot insert " << value << " at front: deque is full." << endl;
            return;
        }
        if (IsEmpty()) {
            front = 0;
            rear = 0;                                  // first value: front == rear
        } else {
            front = (front + CAPACITY - 1) % CAPACITY;
        }
        data[front] = value;
        cout << "Inserted " << value << " at front" << endl;
    }

    // Inserting at the rear moves rear one step FORWARD (with wrap).
    void InsertRear(int value) {
        if (IsFull()) {
            cout << "Cannot insert " << value << " at rear: deque is full." << endl;
            return;
        }
        if (IsEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % CAPACITY;
        }
        data[rear] = value;
        cout << "Inserted " << value << " at rear" << endl;
    }

    // Deleting from the front moves front one step forward.
    void DeleteFront() {
        if (IsEmpty()) {
            cout << "Cannot delete from front: deque is empty." << endl;
            return;
        }
        cout << "Deleted " << data[front] << " from front" << endl;
        if (front == rear) {
            front = -1;                                // removed the only value: reset
            rear = -1;
        } else {
            front = (front + 1) % CAPACITY;
        }
    }

    // Deleting from the rear moves rear one step backward (with wrap).
    void DeleteRear() {
        if (IsEmpty()) {
            cout << "Cannot delete from rear: deque is empty." << endl;
            return;
        }
        cout << "Deleted " << data[rear] << " from rear" << endl;
        if (front == rear) {
            front = -1;                                // removed the only value: reset
            rear = -1;
        } else {
            rear = (rear + CAPACITY - 1) % CAPACITY;
        }
    }

    // I print from front to rear, wrapping around, and stop right after rear so
    // each stored value is shown exactly once (also when rear < front).
    void Display() const {
        if (IsEmpty()) {
            cout << "Deque is empty." << endl;
            return;
        }
        cout << "Deque (front -> rear): ";
        int i = front;
        while (true) {
            cout << data[i] << " ";
            if (i == rear) {
                break;
            }
            i = (i + 1) % CAPACITY;
        }
        cout << "  [front = " << front << ", rear = " << rear << "]" << endl;
    }
};

int main() {
    cout << "=== Task 5: Deque using a circular array ===" << endl;

    // ---------------- Run 1: the main scenario ----------------
    cout << "\n##### Run 1: main scenario #####" << endl;
    ArrayDeque d;

    cout << "\n--- Insert 20 at rear, 10 at front, 30 at rear (expect 10 20 30) ---" << endl;
    d.InsertRear(20);
    d.InsertFront(10);   // front wraps backward from index 0 to index 4
    d.InsertRear(30);
    d.Display();

    cout << "\n--- Delete from rear, then from front (expect 20) ---" << endl;
    d.DeleteRear();
    d.DeleteFront();
    d.Display();

    cout << "\n--- Insert 5 at front, 30 and 40 at rear, 1 at front (expect 1 5 20 30 40) ---" << endl;
    d.InsertFront(5);
    d.InsertRear(30);
    d.InsertRear(40);
    d.InsertFront(1);
    d.Display();
    cout << "IsFull: " << (d.IsFull() ? "yes" : "no") << endl;

    cout << "\n--- Further insertion at either end must be rejected ---" << endl;
    d.InsertFront(99);
    d.InsertRear(99);
    d.Display();         // the contents must be unchanged

    // ---------------- Run 2: only value removed from the front ----------------
    // I use a new deque for each run so that the runs are independent.
    cout << "\n##### Run 2: delete the only value from the front #####" << endl;
    ArrayDeque d2;
    d2.InsertRear(7);
    d2.Display();
    d2.DeleteFront();    // removes the only value; indices reset to -1
    d2.Display();
    cout << "IsEmpty: " << (d2.IsEmpty() ? "yes" : "no") << endl;
    d2.DeleteFront();    // deletion from empty
    d2.DeleteRear();     // deletion from empty at the other end

    // ---------------- Run 3: only value removed from the rear ----------------
    cout << "\n##### Run 3: delete the only value from the rear #####" << endl;
    ArrayDeque d3;
    d3.InsertFront(8);
    d3.Display();
    d3.DeleteRear();     // removes the only value; indices reset to -1
    d3.Display();
    cout << "IsEmpty: " << (d3.IsEmpty() ? "yes" : "no") << endl;
    d3.DeleteRear();     // deletion from empty
    d3.DeleteFront();    // deletion from empty at the other end

    return 0;
}
