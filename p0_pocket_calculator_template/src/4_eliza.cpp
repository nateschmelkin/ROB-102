#include <iostream>
using namespace std;


string promptUserInput() {
    string userInput;
    getline(cin, userInput);
    return userInput;
}

int main() {
    cout << "Hello, I am Eliza. I'll be your therapist today.\nTell me, what is your name?\n";

    string name = promptUserInput();

    cout << "Nice to meet you, " + name + ", how can I help you today?\nWhat is bothering you?\n";

    string problem = promptUserInput();

    cout << "\"" + problem + "\"? Please tell me more. How does that make you feel?\n";

    string feeling = promptUserInput();

    cout << "Intresting intreseting........ well would you look at the time I am afriad we will have to end the session here.\nHave a good rest of your day, " + name + ", I hope to see you again soon!\n";
}