#include <iostream>
using namespace std;

int main() { //delimiter
    
    string inputDist;
    int dist;
    cout << "Enter Distance: ";
    getline(cin, inputDist);
    dist = stoi(inputDist);

    if (dist > 50) {
        cout << "Path Clear";
    } else if (dist <= 50 && dist >= 20) {
        cout << "Thing is close slow down";
    } else {
        cout << "IDK WHAT THIS IS";
    }

}