#include <iostream>

using namespace std;

int main() {
    int numbers[8];

    cout << "Enter 8 integers:" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "Element [" << i << "]: ";
        cin >> numbers[i];
    }

    
    int minVal = numbers[0];
    int maxVal = numbers[0];
    int minIndex = 0;
    int maxIndex = 0;

   
    for (int i = 1; i < 8; i++) {
        //  inequality (<) (>) for only first occurrence index
        if (numbers[i] < minVal) {
            minVal = numbers[i];
            minIndex = i;
        }
        
       
        if (numbers[i] > maxVal) {
            maxVal = numbers[i];
            maxIndex = i;
        }
    }

    cout << "\n--- Results ---" << endl;
    cout << "Smallest value : " << minVal << " (First index: " << minIndex << ")" << endl;
    cout << "Largest value  : " << maxVal << " (First index: " << maxIndex << ")" << endl;

    return 0;
}