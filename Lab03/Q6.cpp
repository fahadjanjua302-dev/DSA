// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// DSA Lab 03 - Task 6: Building a student record application

#include <iostream>
#include<string>
#include <limits>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
};

void displayStudent(const Student* s) {
    cout << "\nStudent Details:" << endl;
    cout << "ID: " << s->rollNo << endl;
    cout << "Name: " << s->name << endl;
    cout << "Marks: " << s->marks << endl;
}

void displayIfExists(const Student* s) {
    if (s != nullptr) {
        displayStudent(s);
    }
    else {
        cout << "\nNo record Available" << endl;
    }
}

void updateMarks(Student* s, float newMarks) {
    cout << "\nUpdating marks using function.\nNew Marks are: " << newMarks << endl;
    s->marks = newMarks;
}

// --- Input validation helpers --------------------------------------------
// cin >> into an int/float leaves the stream in a fail state on non-numeric
// input (e.g. a letter). Once failed, cin refuses every further extraction
// without ever blocking for input again - so a bare `while (cin.fail())`
// loop that just retries `cin >> x` spins forever. Clearing the fail flag
// and discarding the bad characters up to the newline is required before
// retrying, every time.

// Reads an int, re-prompting on non-numeric input. No range check.
int readValidatedInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();                                          // reset fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard bad input
        cout << "Invalid input. Please enter a whole number: ";
    }
    return value;
}

// Reads an int constrained to [minVal, maxVal], re-prompting on bad
// input (non-numeric) or out-of-range values.
int readValidatedIntInRange(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a whole number between "
                 << minVal << " and " << maxVal << ".\n";
            continue;
        }
        if (value < minVal || value > maxVal) {
            cout << "Out of range. Please enter a value between "
                 << minVal << " and " << maxVal << ".\n";
            continue;
        }
        return value;
    }
}

// Reads a float constrained to [minVal, maxVal], re-prompting on bad
// input (non-numeric) or out-of-range values.
float readValidatedFloatInRange(const string& prompt, float minVal, float maxVal) {
    float value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between "
                 << minVal << " and " << maxVal << ".\n";
            continue;
        }
        if (value < minVal || value > maxVal) {
            cout << "Out of range. Please enter a value between "
                 << minVal << " and " << maxVal << ".\n";
            continue;
        }
        return value;
    }
}

// --- Menu helpers ---------------------------------------------------------

// Prints the menu and returns a validated choice between 1 and 5.
int getMenuChoice() {
    cout << "\n1. Create a Student Record.\n"
         << "2. Display Student Record.\n"
         << "3. Update Marks.\n"
         << "4. Delete record.\n"
         << "5. Exit.\n";
    return readValidatedIntInRange("Enter your choice: ", 1, 5);
}

void createRecord(Student*& s) {
    if (s != nullptr) {
        cout << "Student already exists" << endl;
        return;
    }
    s = new Student{};
    cout << "\nEnter Student Details.." << endl;

    s->rollNo = readValidatedInt("Roll Number: ");

    // A failed numeric read above can leave a leftover newline in the
    // buffer even after a successful final read; cin >> ws (used by
    // getline below) skips it, so no separate cin.ignore() is needed here.
    cout << "Name: ";
    getline(cin >> ws, s->name);   // allows names containing spaces

    s->marks = readValidatedFloatInRange("Marks (0-100): ", 0, 100);
}

void updateRecord(Student* s) {
    if (s == nullptr) {
        cout << "No student exists.." << endl;
        return;
    }
    float newMarks = readValidatedFloatInRange("Enter new Marks between 0 and 100: ", 0, 100);
    updateMarks(s, newMarks);
}

void deleteRecord(Student*& s) {
    if (s == nullptr) {
        cout << "No student exists to delete" << endl;
        return;
    }
    delete s;
    s = nullptr;
    cout << "Record deleted successfully." << endl;
}

// Runs the entire menu-driven interface as a single self-contained function.
// Manages the one dynamically allocated Student record for the whole session
// and guarantees the record is freed before returning.
void runStudentManagementMenu() {
    Student* s = nullptr;

    cout << "Welcome to Student Management System" << endl;

    while (true) {
        int choice = getMenuChoice();

        switch (choice) {
        case 1:
            createRecord(s);
            break;
        case 2:
            displayIfExists(s);
            break;
        case 3:
            updateRecord(s);
            break;
        case 4:
            deleteRecord(s);
            break;
        case 5:
            if (s != nullptr) {
                delete s;
                s = nullptr;
            }
            cout << "Exiting. Goodbye!" << endl;
            return;   // leaves the function (and the loop) cleanly
        }
    }
}

int main() {
    runStudentManagementMenu();
    return 0;
}