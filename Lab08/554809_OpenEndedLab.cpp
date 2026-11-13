// Name         : Fahad Ali
// Registration : 554809
// Section      : BSCS-15_ D
// Lab          : Open Ended Lab - Student Help Desk

// DESIGN EXPLANATION
// I chose two data structures, both written by me without STL containers.
// 
// 1) Binary Search Tree (BST) keyed by roll number, to store the students.
//    - Roll numbers must be unique and I search by roll number. In a BST the
//      walk that checks for a duplicate is the same walk that finds where to
//      insert, so rejecting duplicates costs me nothing extra.
//    - An in-order traversal displays the students sorted by roll number
//      without any extra sorting code.
//    - It has no fixed capacity, so I never have a full array problem.

// 2) Linked-list Queue (FIFO) for help requests.
//    - A help desk should serve the student who asked first, which is
//      first-in-first-out. A stack would serve the newest request first and
//      could leave early requests waiting forever.
//    - With front and rear pointers, enqueue and dequeue are both O(1), and
//      repeated requests from the same student are just separate nodes.
//    - Before I enqueue a request, I use the BST search to confirm the
//      student is registered, so the two structures work together.

// COMPLEXITY SUMMARY (n = number of students, h = height of the BST)
//    Add student     : O(h), worst case O(n) if I insert roll numbers in
//                      sorted order because the tree becomes a chain.
//                      Balanced case is O(log n).
//    Search student  : O(h), worst case O(n), balanced case O(log n).
//    Display all     : O(n), I visit every node once.
//    Enqueue/Dequeue : O(1) each (enqueue also does one BST search first).

// Alternative structure I would suggest: a sorted array with binary search
// (O(log n) search but O(n) insertion because of shifting), or an AVL tree,
// which keeps the height at O(log n) so add and search stay O(log n) even
// in the worst case.

// External code: none. I wrote this program myself.

#include <iostream>
#include <string>
using namespace std;

// Student record: a unique roll number and a name.
struct Student {
    int rollNo;
    string name;
};

// BST node that holds one student and links to the smaller/larger roll numbers.
struct TreeNode {
    Student data;
    TreeNode* left;
    TreeNode* right;
};

class StudentTree {
private:
    TreeNode* root;

    // I print the left subtree, then this node, then the right subtree, so the
    // output comes out sorted by roll number.
    static void inorder(const TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << "  Roll No: " << node->data.rollNo
            << "  |  Name: " << node->data.name << endl;
        inorder(node->right);
    }

    // I delete the children first and the node last (post-order), so I never
    // touch a node after it has been freed.
    static void destroy(TreeNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    StudentTree() : root(nullptr) {}
    ~StudentTree() { clear(); }

    bool isEmpty() const { return root == nullptr; }

    // Worst-case time complexity: O(n) (O(h) in general; O(log n) if balanced).
    // I walk down the tree once. If I meet the same roll number I reject it,
    // otherwise I attach the new node where the walk ended.
    bool add(int rollNo, const string& name) {
        TreeNode* parent = nullptr;
        TreeNode* current = root;

        while (current != nullptr) {
            if (rollNo == current->data.rollNo) {
                return false;                      // duplicate roll number
            }
            parent = current;
            current = (rollNo < current->data.rollNo) ? current->left
                : current->right;
        }

        TreeNode* node = new TreeNode;
        node->data.rollNo = rollNo;
        // A std::string copies its own text when I assign it, so each node
        // keeps its own copy of the name.
        node->data.name = name;
        node->left = nullptr;
        node->right = nullptr;

        if (parent == nullptr)           root = node;          // first student
        else if (rollNo < parent->data.rollNo) parent->left = node;
        else                             parent->right = node;
        return true;
    }

    // Worst-case time complexity: O(n) (O(h) in general; O(log n) if balanced).
    // I go left or right at each node until I find the roll number or run out
    // of tree. I return nullptr when the student is not registered.
    TreeNode* search(int rollNo) const {
        TreeNode* current = root;
        while (current != nullptr) {
            if (rollNo == current->data.rollNo) return current;
            current = (rollNo < current->data.rollNo) ? current->left
                : current->right;
        }
        return nullptr;
    }

    // O(n): every student is visited exactly once.
    void displayAll() const {
        if (isEmpty()) {
            cout << "  No students are registered yet." << endl;
            return;
        }
        inorder(root);
    }

    void clear() {
        destroy(root);
        root = nullptr;
    }
};

// Queue node for a help request. I only store the roll number.
struct QueueNode {
    int rollNo;
    QueueNode* next;
};

class HelpQueue {
private:
    QueueNode* front;   // earliest waiting request (served first)
    QueueNode* rear;    // newest request (added here)

public:
    HelpQueue() : front(nullptr), rear(nullptr) {}
    ~HelpQueue() { clear(); }

    bool isEmpty() const { return front == nullptr; }

    // O(1): I attach the new request after the current rear.
    // The same roll number can be queued many times, which is allowed.
    void enqueue(int rollNo) {
        QueueNode* node = new QueueNode;
        node->rollNo = rollNo;
        node->next = nullptr;

        if (rear == nullptr) {          // queue was empty
            front = node;
            rear = node;
        }
        else {
            rear->next = node;
            rear = node;
        }
    }

    // O(1): I remove the front node, which is the earliest request waiting.
    // Returns false if there is nothing to serve.
    bool dequeue(int& rollNo) {
        if (isEmpty()) return false;

        QueueNode* old = front;
        rollNo = old->rollNo;
        front = front->next;
        if (front == nullptr) rear = nullptr;   // queue became empty
        delete old;
        return true;
    }

    // O(n): shows the waiting requests from earliest to latest.
    void display() const {
        if (isEmpty()) {
            cout << "  No help requests are waiting." << endl;
            return;
        }
        int position = 1;
        for (const QueueNode* cur = front; cur != nullptr; cur = cur->next) {
            cout << "  " << position++ << ". Roll No: " << cur->rollNo << endl;
        }
    }

    void clear() {
        while (front != nullptr) {
            QueueNode* old = front;
            front = front->next;
            delete old;
        }
        rear = nullptr;
    }
};

// Menu helpers
void addStudent(StudentTree& tree) {
    int rollNo;
    string name;

    cout << "Enter roll number: ";
    cin >> rollNo;
    cin.ignore(1000, '\n');
    cout << "Enter name: ";
    getline(cin, name);

    if (tree.add(rollNo, name)) {
        cout << "Student " << rollNo << " added successfully." << endl;
    }
    else {
        cout << "Error: roll number " << rollNo
            << " already exists. Student not added." << endl;
    }
}

void searchStudent(const StudentTree& tree) {
    if (tree.isEmpty()) {
        cout << "No students are registered yet, so there is nothing to search." << endl;
        return;
    }
    int rollNo;
    cout << "Enter roll number to search: ";
    cin >> rollNo;

    TreeNode* found = tree.search(rollNo);
    if (found != nullptr) {
        cout << "Found -> Roll No: " << found->data.rollNo
            << "  |  Name: " << found->data.name << endl;
    }
    else {
        cout << "Student with roll number " << rollNo << " was not found." << endl;
    }
}

void helpRequestMenu(const StudentTree& tree, HelpQueue& queue) {
    int choice;
    cout << "\n--- Help Requests ---" << endl;
    cout << "1. Add a help request" << endl;
    cout << "2. Serve the earliest request" << endl;
    cout << "3. Show waiting requests" << endl;
    cout << "4. Back" << endl;
    cout << "Choose: ";
    cin >> choice;

    if (choice == 1) {
        int rollNo;
        cout << "Enter roll number requesting help: ";
        cin >> rollNo;
        // I only accept requests from students who are registered.
        if (tree.search(rollNo) == nullptr) {
            cout << "Rejected: roll number " << rollNo
                << " is not registered." << endl;
        }
        else {
            queue.enqueue(rollNo);
            cout << "Help request added for roll number " << rollNo << "." << endl;
        }
    }
    else if (choice == 2) {
        int rollNo;
        if (queue.dequeue(rollNo)) {
            TreeNode* student = tree.search(rollNo);
            cout << "Now serving roll number " << rollNo;
            if (student != nullptr) cout << " (" << student->data.name << ")";
            cout << "." << endl;
        }
        else {
            cout << "No help requests are waiting." << endl;
        }
    }
    else if (choice == 3) {
        queue.display();
    }
    else if (choice != 4) {
        cout << "Invalid option." << endl;
    }
}

int main() {
    StudentTree students;
    HelpQueue requests;
    int choice = 0;

    do {
        cout << "\n===== Student Help Desk =====" << endl;
        cout << "1. Add a student" << endl;
        cout << "2. Search by roll number" << endl;
        cout << "3. Display all students" << endl;
        cout << "4. Help requests (queue)" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose: ";
        if (!(cin >> choice)) break;      // stop cleanly if input ends

        switch (choice) {
        case 1: addStudent(students); break;
        case 2: searchStudent(students); break;
        case 3:
            cout << "\n--- All Students (sorted by roll number) ---" << endl;
            students.displayAll();
            break;
        case 4: helpRequestMenu(students, requests); break;
        case 5: cout << "Exiting..." << endl; break;
        default: cout << "Invalid option. Please try again." << endl;
        }
    } while (choice != 5);

    // I free all dynamically allocated memory before the program ends.
    students.clear();
    requests.clear();
    return 0;
}