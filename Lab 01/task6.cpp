#include <iostream>

using namespace std;

int main() {
    int arr[10];

    cout << "Enter 10 integers:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Element [" << i << "]: ";
        cin >> arr[i];
    }

    int uniqueCount = 0; 

    for (int i = 0; i < 10; i++) {
        bool isDuplicate = false;

        // Check if arr[i] already appeared in the earlier part of the array
        for (int k = 0; k < i; k++) {
            if (arr[k] == arr[i]) {
                isDuplicate = true;
                break;
            }
        }

        // If it's the first occurrence, shift it to the front of the array
        if (!isDuplicate) {
            arr[uniqueCount] = arr[i];
            uniqueCount++;
        }
    }

    // Display unique values
    cout << "\nUnique values: {";
    for (int i = 0; i < uniqueCount; i++) {
        cout << arr[i] <<" ";
    }
   

    cout << "Count of unique values: " << uniqueCount << endl;

    return 0;
}