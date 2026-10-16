// Name: Fahad Ali
// Registration No: 554809
// Section: BSCS-15D
// Lab 06 - Task 3: Reversing a word using a stack

#include <iostream>
#include <string>
using namespace std;

const int MAX_LEN = 20;
char stackArr[MAX_LEN];
int top = -1;

bool isEmpty() { return top == -1; }
bool isFull()  { return top == MAX_LEN - 1; }

void push(char c) {
    if (isFull()) {
        cout << "Stack is full." << endl;
        return;
    }
    stackArr[++top] = c;
}

char pop() {
    if (isEmpty())
        return '\0';
    return stackArr[top--];
}

int main() {
    string word;
    cout << "Enter a word (max " << MAX_LEN << " characters): ";
    cin >> word;

    // Check the input length before pushing
    if ((int)word.length() > MAX_LEN) {
        cout << "Error: word has " << word.length()
             << " characters; the limit is " << MAX_LEN << "." << endl;
        return 0;
    }

    for (size_t i = 0; i < word.length(); i++)
        push(word[i]);

    cout << "Reversed word: ";
    while (!isEmpty())
        cout << pop();
    cout << endl;

    return 0;
}
