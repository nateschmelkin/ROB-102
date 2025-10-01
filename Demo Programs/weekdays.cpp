#include <iostream>

using namespace std;

int main() {
    int num;

    cout << "Enter a day number: \n";
    cin >> num;

    switch (num) {
    case 1:
        cout << "Monday\n";
        break;

    case 2:
        cout << "Tuesday\n";
        break;

    case 3:
        cout << "Wednesday\n";
        break;

    case 4:
        cout << "Thursday\n";
        break;

    case 5:
        cout << "Friday\n";
        break;

    case 6: case 7:
        cout << "Weekend\n";
        break;

    default:
        cout << "You suck\n";
        break;
    }
}