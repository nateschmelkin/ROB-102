#include <gtest/gtest.h>

#include <pocket_calculator/common/utils.h>
#include <test_utils.h>

TEST(HelloWorld, TestOutput) {
    OutputTuple output = getOutput("hello_world", "../test/1_hello_world.output.correct");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}  

TEST(GoBlue, TestOutput) {
    OutputTuple output = getOutput("go_blue", "../test/2_go_blue.output.correct");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(FightSong, TestOutput) {
    OutputTuple output = getOutput("fight_song", "../test/3_fight_song.output.correct");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(Eliza, TestInputOutput) {
    OutputTuple output = getOutput("eliza", "../test/4_eliza.output.correct", "../test/4_eliza.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(CalcOp, TestAdd) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_add.output.correct", "../test/5_calc_op_add.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(CalcOp, TestSubtract) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_subtract.output.correct", "../test/5_calc_op_subtract.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(CalcOp, TestMultiply) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_multiply.output.correct", "../test/5_calc_op_multiply.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}   

TEST(CalcOp, TestDivide) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_divide.output.correct", "../test/5_calc_op_divide.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(CalcOp, TestDivideFloat) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_float.output.correct", "../test/5_calc_op_float.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(correct_output, actual_output) << "Make sure your output is correct!";
}

TEST(CalcOp, TestDivideByZero) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_zero.output.correct", "../test/5_calc_op_zero.input");
    std::string error_output = std::get<2>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, -1);
    ASSERT_EQ(error_output, "Error: Divide by zero attempted!!!\n") << "Make sure your output is going to stderr not stdout!";
}

TEST(CalcOp, TestBadOp) {
    OutputTuple output = getOutput("calc_op", "../test/5_calc_op_bad_op.output.correct", "../test/5_calc_op_bad_op.input");
    std::string error_output = std::get<2>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(return_code, -1);
    ASSERT_EQ(error_output, "Error: specified operation (a) not recognized.\n") << "Make sure your output is going to stderr not stdout!";
}

TEST(PocketCalculator, TestAddTwoNumbers) {
    float result = addTwoNumbers(3, 3);
    ASSERT_FLOAT_EQ(6, result);

    result = addTwoNumbers(5.5, 3.4);
    ASSERT_FLOAT_EQ(8.9, result);

    result = addTwoNumbers(5, 3.4);
    ASSERT_FLOAT_EQ(8.4, result);
}

TEST(PocketCalculator, TestSubtractTwoNumbers) {
    float result = subtractTwoNumbers(3, 3);
    ASSERT_FLOAT_EQ(0, result);

    result = subtractTwoNumbers(5.5, 3.4);
    ASSERT_FLOAT_EQ(2.1, result);

    result = subtractTwoNumbers(5, 3.4);
    ASSERT_FLOAT_EQ(1.6, result);
}

TEST(PocketCalculator, TestMultiplyTwoNumbers) {
    float product;
    multiplyTwoNumbers(3, 4, product);
    ASSERT_FLOAT_EQ(12, product);

    multiplyTwoNumbers(5.5, 3, product);
    ASSERT_FLOAT_EQ(16.5, product);

    multiplyTwoNumbers(2.5, 3.5, product);
    ASSERT_FLOAT_EQ(8.75, product);
}

TEST(PocketCalculator, TestDivideTwoNumbers) {
    float quotient;
    bool divided_by_zero = divideTwoNumbers(9, 3, quotient);
    ASSERT_FLOAT_EQ(3, quotient);
    ASSERT_FALSE(divided_by_zero);

    divided_by_zero = divideTwoNumbers(6.5, 2.5, quotient);
    ASSERT_FLOAT_EQ(2.6, quotient);
    ASSERT_FALSE(divided_by_zero);

    divided_by_zero = divideTwoNumbers(10, 0, quotient);
    ASSERT_TRUE(divided_by_zero);
}

TEST(PocketCalculator, TestGetNumber) {
    float input_number = 5.0;
    float result;
    std::string prompt = "not_empty";
    std::stringstream output_stream;
    std::stringstream input_stream;
    input_stream << input_number;
    getNumber(output_stream, input_stream, result);
    output_stream >> prompt;
    ASSERT_NE(prompt, "not_empty") << "Make sure you're prompting the user!\n";
    ASSERT_EQ(result, input_number);
}

TEST(PocketCalculator, TestGetOperatorBasic) {
    char input_character = '*';
    char result;
    bool invalid_operator = true;
    std::stringstream output_stream;
    std::stringstream input_stream;
    input_stream << input_character;
    invalid_operator = getOperator(output_stream, input_stream, result);
    ASSERT_EQ(result, input_character);
    ASSERT_FALSE(invalid_operator);
}   

TEST(PocketCalculator, TestGetOperatorPromptUser) {
    char input_character = '*';
    char result;
    bool invalid_operator = true;
    std::string prompt = "not_empty";
    std::stringstream output_stream;
    std::stringstream input_stream;
    input_stream << input_character;
    invalid_operator = getOperator(output_stream, input_stream, result);
    output_stream >> prompt;
    ASSERT_NE(prompt, "not_empty") << "Make sure you're prompting the user!\n";
}

TEST(PocketCalculator, TestGetOperatorInvalidOp) {
    char input_character = 'p';
    char result;
    bool invalid_operator = true;
    std::string prompt = "not_empty";
    std::stringstream output_stream;
    std::stringstream input_stream;
    input_stream << input_character;
    invalid_operator = getOperator(output_stream, input_stream, result);
    output_stream >> prompt;
    ASSERT_TRUE(invalid_operator);
}

TEST(PocketCalculator, TestPerformOperation) {
    float result;
    bool divided_by_zero;
    divided_by_zero = performOperation(3, '+', 4, result);
    ASSERT_FLOAT_EQ(7, result);
    ASSERT_FALSE(divided_by_zero);

    divided_by_zero = performOperation(6, '-', 4, result);
    ASSERT_FLOAT_EQ(2, result);
    ASSERT_FALSE(divided_by_zero);

    divided_by_zero = performOperation(3, '*', 4, result);
    ASSERT_FLOAT_EQ(12, result);
    ASSERT_FALSE(divided_by_zero);

    divided_by_zero = performOperation(8, '/', 4, result);
    ASSERT_FLOAT_EQ(2, result);
    ASSERT_FALSE(divided_by_zero);

    divided_by_zero = performOperation(8, '/', 0, result);
    ASSERT_FLOAT_EQ(2, result);  // result should not change value if an error is requested
    ASSERT_TRUE(divided_by_zero);
}

TEST(PocketCalculator, TestMainBasicOperators) {
    OutputTuple output = getOutput("pocket_calculator", "../test/6_pocket_calc_basic_operators.output.correct",
                                   "../test/6_pocket_calc_basic_operators.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(correct_output, actual_output);
    ASSERT_EQ(return_code, 0);
}

TEST(PocketCalculator, TestMainBadOperator) {
    OutputTuple output = getOutput("pocket_calculator", "../test/6_pocket_calc_bad_operator.output.correct",
                                   "../test/6_pocket_calc_bad_operator.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    std::string error_output = std::get<2>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(correct_output, actual_output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(error_output, "Error: specified operation (k) not recognized\n");
}

TEST(PocketCaculator, TestMainBadOperatorDuplicate) {
    OutputTuple output = getOutput("pocket_calculator", "../test/6_pocket_calc_bad_operator_duplicate.output.correct",
                                   "../test/6_pocket_calc_bad_operator_duplicate.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    std::string error_output = std::get<2>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(correct_output, actual_output);
    ASSERT_EQ(return_code, 0);
    ASSERT_EQ(error_output, "Error: specified operation (p) not recognized\nError: specified operation (o) not recognized\nError: specified operation (l) not recognized\n");
}

TEST(PocketCalculator, TestMainDivideByZero) {
    OutputTuple output = getOutput("pocket_calculator", "../test/6_pocket_calc_divide_by_zero.output.correct",
                                   "../test/6_pocket_calc_divide_by_zero.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    std::string error_output = std::get<2>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(correct_output, actual_output);
    ASSERT_EQ(return_code, -1);
    ASSERT_EQ(error_output, "Error: Divide by zero attempted!!!\n");
}

TEST(PocketCalculator, TestMainEarlyQuit) {
    OutputTuple output = getOutput("pocket_calculator", "../test/6_pocket_calc_early_quit.output.correct",
                                   "../test/6_pocket_calc_early_quit.input");
    std::string correct_output = std::get<0>(output);
    std::string actual_output = std::get<1>(output);
    int return_code = std::get<3>(output);
    ASSERT_EQ(correct_output, actual_output);
    ASSERT_EQ(return_code, 0);
}