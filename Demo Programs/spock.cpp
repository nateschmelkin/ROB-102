#include <iostream>
#include <string>
#include <limits>
using namespace std;

enum handstates {
    ROCK = 0,
    PAPER,
    SCISSORS,
    LIZARD,
    SPOCK
};

int main() {
    handstates handState;
    char currentButton;

    cout << "Please enter your corresponding integer for starting hand move\n";

    int input;
    cin >> input;

    if (cin.fail() || input < 0 || input > 4) {
        cout << "You r dumb and broke the thing";
        return -1;
    }

    handState = static_cast<handstates>(input);

    while (true) {
        cout << "\nPlease enter your key press: ";
        cin >> currentButton;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        cout << endl;

        switch (handState) {
            case ROCK:
                switch (currentButton) {
                    case 'c':
                        handState = SCISSORS;
                        cout << "HandState is SCISSORS\n";
                        break;
                    case 'r':
                        handState = LIZARD;
                        cout << "HandState is LIZARD\n";
                        break;
                    default:
                        cout << "Invalid key press for ROCK\n";
                        break;
                }
                break;

            case SCISSORS:
                switch (currentButton) {
                    case 'd':
                        handState = LIZARD;
                        cout << "HandState is LIZARD\n";
                        break;
                    case 't':
                        handState = PAPER;
                        cout << "HandState is PAPER\n";
                        break;
                    default:
                        cout << "Invalid key press for SCISSORS\n";
                        break;
                }
                break;

            case LIZARD:
                switch (currentButton) {
                    case 'e':
                        handState = PAPER;
                        cout << "HandState is PAPER\n";
                        break;
                    case 'p':
                        handState = SPOCK;
                        cout << "HandState is SPOCK\n";
                        break;
                    default:
                        cout << "Invalid key press for LIZARD\n";
                        break;
                }
                break;

            case PAPER:
                switch (currentButton) {
                    case 'i':
                        handState = SPOCK;
                        cout << "HandState is SPOCK\n";
                        break;
                    case 'o':
                        handState = ROCK;
                        cout << "HandState is ROCK\n";
                        break;
                    default:
                        cout << "Invalid key press for PAPER\n";
                        break;
                }
                break;

            case SPOCK:
                switch (currentButton) {
                    case 'v':
                        handState = ROCK;
                        cout << "HandState is ROCK\n";
                        break;
                    case 'm':
                        handState = SCISSORS;
                        cout << "HandState is SCISSORS\n";
                        break;
                    default:
                        cout << "Invalid key press for SPOCK\n";
                        break;
                }
                break;
        }
    }
}