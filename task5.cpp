#include <iostream>

using namespace std;

void reverseArray(int arr[], int left, int right) {
    // Base case: stop when indices meet or cross
    if (left >= right) {
        return;
    }

    // Swap elements at left and right indices
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;

    // Move inward towards the center
    reverseArray(arr, left + 1, right - 1);
}

int main() {
    int numbers[6];
    int size = 6;

    cout << "Enter 6 integers:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element [" << i << "]: ";
        cin >> numbers[i];
    }

    // Reverse array recursively
    reverseArray(numbers, 0, size - 1);

    cout << "\nReversed array: ";
    for (int i : numbers) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}