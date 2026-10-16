// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// Lab 06 - Task 6: Customer service queue (menu driven)
//
// ===================== THEORETICAL EXPLANATION =====================
// 1. Queue concept (FIFO):
//    A queue is a linear data structure that follows First In First Out.
//    The customer who takes a token first is served first. enqueue()
//    inserts at the REAR and dequeue() removes from the FRONT. In this
//    program the "Add customer" option is enqueue, "Serve next" is
//    dequeue, "View next" is peekFront and "Display queue" prints the
//    items from front to rear.
//
// 2. Implementation used:
//    A linear array of size 5 with two indices, front and rear.
//      - Empty queue : front = rear = -1
//      - First insert: front = rear = 0
//      - Later insert: rear++
//      - Removal     : front++ (or reset both to -1 if it was the last item)
//      - Full / blocked insertion: rear == SIZE - 1
//    Every operation takes O(1) time except display, which is O(n).
//
// 3. The limitation (why insertion can be blocked even if space exists):
//    Items are never shifted and indices never wrap around. When a
//    customer is served, front moves forward and the slot behind it is
//    freed, but rear stays where it is. So the insertion test
//    (rear == SIZE - 1) still says "full" even though the freed slots
//    at the start of the array are unused.
//    Example: fill with tokens 1..5 (front=0, rear=4). Serve two
//    customers -> front=2, rear=4. Only 3 customers are waiting, yet
//    Add customer is blocked because rear is 4. The wasted slots
//    (index 0 and 1) can only be reused after the queue becomes empty
//    and front/rear are reset to -1.
//
// 4. Why it is acceptable / how to fix it:
//    It is a known drawback of the simple linear queue (false overflow).
//    It can be solved by (a) shifting all items left after each dequeue,
//    which costs O(n) per removal, or (b) a circular queue where
//    rear = (rear + 1) % SIZE, which reuses freed slots in O(1). The lab
//    does not require the circular queue, so this program intentionally
//    keeps the linear behaviour to demonstrate the limitation.
// ===================================================================

#include <iostream>
using namespace std;

const int SIZE = 5;
int items[SIZE];
int front = -1;
int rear = -1;

void enqueue(int value) {
    if (rear == SIZE - 1) {
        cout << "Cannot add customer: insertion is blocked (rear is at the last index)." << endl;
        if (front > 0)
            cout << "Note: free slots exist at the start of the array, but they are reused only after the queue becomes empty." << endl;
        return;
    }
    if (front == -1)
        front = 0;
    items[++rear] = value;
    cout << "Customer with token " << value << " added to the queue." << endl;
}

void dequeue() {
    if (front == -1) {
        cout << "No customers to serve: queue is empty." << endl;
        return;
    }
    cout << "Serving customer with token " << items[front] << "." << endl;
    if (front == rear)
        front = rear = -1;
    else
        front++;
}

void peekFront() {
    if (front == -1) {
        cout << "No customers waiting: queue is empty." << endl;
        return;
    }
    cout << "Next customer to be served: token " << items[front] << endl;
}

void display() {
    if (front == -1) {
        cout << "Queue is empty." << endl;
        return;
    }
    cout << "Customers waiting (front to rear): ";
    for (int i = front; i <= rear; i++)
        cout << items[i] << " ";
    cout << endl;
}

int main() {
    int choice, token;

    do {
        cout << "\n===== Customer Service Queue =====" << endl;
        cout << "1. Add customer" << endl;
        cout << "2. Serve next" << endl;
        cout << "3. View next" << endl;
        cout << "4. Display queue" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter token number: ";
                cin >> token;
                enqueue(token);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                peekFront();
                break;
            case 4:
                display();
                break;
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }
    } while (choice != 5);

    return 0;
}
