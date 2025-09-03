/*
 * File: 6_pocket_calc.cpp
 *
 * Let's write an infix calculator program for real numbers with variables
 * that takes numbers from user input, uses functions for modularity,
 * and performs calulations with infinitely many consecutive operations!
 */

#include <iostream>
#include <pocket_calculator/common/utils.h>

using namespace std;
// *** Task: Add any extra helper functions you want here *** //

// *** End Student Code *** //


int main() {
  // Let's declare our variables!
  float my_number, my_other_number; // Calculation operands
  float result_number;
  char my_operator; // Character representing operation to perform
  bool first_run = true; // To help get 2 numbers initially
  while (true) {
    if (first_run) {
      getNumber(cout, cin, my_number);
      first_run = false;
    }
    while (getOperator(cout, cin, my_operator));
    if (my_operator == 'q') {
      return 0;
    }
    getNumber(cout, cin, my_other_number);
    if (performOperation(my_number, my_operator, my_other_number, result_number)) {
      return -1;
    }
    cout << my_number << " " << my_operator << " " << my_other_number << " = " << result_number << "\n";
    my_number = result_number;
  }

  // *** End Student Code *** //
}
