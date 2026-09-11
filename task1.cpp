#include<iostream>

using namespace std;

int main() {
    int numbers[] = { 2,4,6,8,10 };
    numbers[2] = 7;
    for (int n : numbers)
        cout << n << " ";// output will be 2 4 7 8 10

}