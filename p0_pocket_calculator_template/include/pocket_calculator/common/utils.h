/**
 * File: utils.h
 *
 * Definitions for utility functions to be used in driver programs.
 */

#ifndef POCKET_CALCULATOR_INCLUDE_COMMON_UTILS_H
#define POCKET_CALCULATOR_INCLUDE_COMMON_UTILS_H

#include <iostream>

/**
 * Adds two numbers and returns their sum.
 * @param  operand1 The first number to be added.
 * @param  operand2 The second number to be added.
 * @return  The sum of the arguments.
 */
float addTwoNumbers(float operand1, float operand2);

/**
 * Subtracts two numbers and returns the result.
 * @param  operand1 The number to be subtracted from.
 * @param  operand2 The amount to be subtracted.
 * @return  The difference of the arguments.
 */
float subtractTwoNumbers(float operand1, float operand2);

/**
 * Multiplies two numbers and stores the result in the third argument.
 * @param  operand1 The first number to be multipled.
 * @param  operand2 The second number to multiply the first by.
 * @param[out]  product The product of the arguments.
 */
void multiplyTwoNumbers(float operand1, float operand2, float &product);

/**
 * Divides the first argument by the second argument and stores the result in the third argument.
 * @param  operand1 The numerator of the operation.
 * @param  operand2 the denominator of the operation.
 * @param[out]  quotient The quotient, unchanged if return is true.
 * @return  A bool, true if the denominator is zero, false otherwise.
 */
bool divideTwoNumbers(float operand1, float operand2, float &quotient);

/**
 * Prompts the user to input a number and stores the value in the argument.
 * @param[out]  output_stream The stream on which to prompt the user.
 * @param[in, out]  input_stream The stream on which to take user input.
 * @param[out]  number The number collected from the user.
 *
 * NOTE: The user is assumed to input a valid floating point number on the input stream.
 */
void getNumber(std::ostream& output_stream, std::istream& input_stream, float &number);

/**
 * Prompts the user to input an operator, stores the operator, and checks for errors with the operator.
 * @param[out]  output_stream The stream on which to prompt the user.
 * @param[in, out]  input_stream The stream on which to take user input.
 * @param[out]  operation The operator collected from the user.
 * @return  A bool, true if the operator is not one of (+, -, *, /, q), false otherwise.
 *
 * NOTE: The user is assumed to input a single character on the input stream.
 */
bool getOperator(std::ostream& output_stream, std::istream& input_stream, char &operation);

/**
 * Performs an operation on two operands and stores the result.
 * @param  operand1 The first operand to be passed into the operation.
 * @param  operation The operation to be performed, assumed to be one of (+, -, *, /).
 * @param  operand2 The second operand to be passed into the operation.
 * @param[out]  result The result of the operation, unchanged if return is true.
 * @return  A bool, true if division by zero was requested, false otherwise.
 */
bool performOperation(float operand1, char operation, float operand2, float &result);

#endif  // POCKET_CALCULATOR_INCLUDE_COMMON_UTILS_H