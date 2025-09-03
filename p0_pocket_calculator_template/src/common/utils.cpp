/**
 * File: utils.cpp
 *
 * Utility functions to be used in driver programs. 
 */

#include <pocket_calculator/common/utils.h>


float addTwoNumbers(float operand1, float operand2) {
    return operand1 + operand2;

    // *** End student code *** //
}

float subtractTwoNumbers(float operand1, float operand2) {
    return operand1 - operand2;

    // *** End student code *** //
}

void multiplyTwoNumbers(float operand1, float operand2, float &product) {
    product = operand1 * operand2;
    // *** End student code *** //
}

bool divideTwoNumbers(float operand1, float operand2, float &quotient) {
    if (operand2 == 0) {
        std::cerr << "Error: Divide by zero attempted!!!\n";
        return true;
    }
    quotient = operand1 / operand2;
    return false;

    // *** End student code *** //
}

void getNumber(std::ostream& output_stream, std::istream& input_stream, float &number) {
    output_stream << "Please type a number and press enter: ";
    input_stream >> number;
    // *** End student code *** //
}

bool getOperator(std::ostream& output_stream, std::istream& input_stream, char &operation) {
    output_stream << "Please type a math operator (one of: + - * / or q to quit): ";
    input_stream >> operation;
    if (operation != '+' && operation != '-' && operation != '*' && operation != '/' && operation != 'q') {
        std::cerr << "Error: specified operation (" << operation << ") not recognized\n";
        return true;
    }
    if (operation == 'q') {
        output_stream << "Calculator: quitting now\n";
    }
    return false;

    // *** End student code *** //
}

bool performOperation(float operand1, char operation, float operand2, float &result) {
    switch (operation) {
        case '+':
            result = addTwoNumbers(operand1, operand2);
            break;
        
        case '-':
            result = subtractTwoNumbers(operand1, operand2);
            break;

        case '*':
            multiplyTwoNumbers(operand1, operand2, result);
            break;

        case '/':
            if (divideTwoNumbers(operand1, operand2, result)) {
                return true;
            }
            break;

        case 'q':
            break;

        default:
            break;
    }
    return false;
}
