#include <iostream>
using namespace std;

float number1;
float number2;
char operation;
float result;
bool killError = false;

void inputPhase() {
    cout << "Please type a number and press enter: ";
    cin >> number1;
    cout << "Please type a math operator (one of: + - * or /): ";
    cin >> operation;
    cout << "Please type another number and press enter: ";
    cin >> number2;
}

bool isDividingByZero() {
    if (number2 == 0) {
        cerr << "Error: Divide by zero attempted!!!\n";
        return true;
    }
    return false;
}

void calculateResult() {
    switch (operation) {
        case '+':
            result = number1 + number2;
            break;
        
        case '-':
            result = number1 - number2;
            break;

        case '*':
            result = number1 * number2;
            break;  

        case '/':
            if (isDividingByZero()) {
                killError = true;
            }
            result = number1 / number2;
            break;

        default:
            cerr << "Error: specified operation (" << operation << ") not recognized.\n";
            killError = true;
            break;
        }
}

void outputResult() {
    cout << "Here's the result of the operation!\n";
    cout << number1 << " " << operation << " " << number2 << " = " << result << "\n";
}


int main() {
    inputPhase();
    calculateResult();
    if (killError) {
        return -1;
    }
    outputResult();
}