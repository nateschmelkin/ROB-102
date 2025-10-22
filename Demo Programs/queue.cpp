#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<string> cities;
    cities.push("Ann Arbor");
    cities.push("Detroit");
    cities.push("Lansing");
    cities.push("Kalamazoo");

    cities.pop();
    cout << "First " << cities.front() << endl;
    cout << "Last " << cities.back() << endl;
}