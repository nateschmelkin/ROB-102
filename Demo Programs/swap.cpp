#include <iostream>

using namespace std;

void swap(int &num1, int &num2) {
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

int main() {
    int num1, num2;
    cout << "Enter number 1\n";
    cin >> num1;
    cout << "Enter number 2\n";
    cin >> num2;
    swap(num1, num2);
    cout << "New num1: " << num1 << "; New num2: " << num2;
}