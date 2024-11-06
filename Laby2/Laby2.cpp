#include <iostream>
#include "CNumber.h"

void testSetFromInt() {
    CNumber num;

    num = 12345;
    std::cout << "Test setFromInt (12345): " << num.sToStr() << " (Expected: 12345)" << std::endl;

    num = -6789;
    std::cout << "Test setFromInt (-6789): " << num.sToStr() << " (Expected: -6789)" << std::endl;

    num = 0;
    std::cout << "Test setFromInt (0): " << num.sToStr() << " (Expected: 0)" << std::endl;
}

void testAssignmentOperator() {
    CNumber num1, num2;

    num1 = 56789;
    num2 = num1;

    std::cout << "Test assignment operator (num2 = num1): " << num2.sToStr() << " (Expected: 56789)" << std::endl;
}

void testAddition() {
    CNumber num1, num2, result;

    num1 = 1234;
    num2 = 567;
    result = num1 + num2;
    std::cout << "Test addition (1234 + 567): " << result.sToStr() << " (Expected: 1801)" << std::endl;

    num1 = 9999;
    num2 = 1;
    result = num1 + num2;
    std::cout << "Test addition (9999 + 1): " << result.sToStr() << " (Expected: 10000)" << std::endl;
}

void testNegativeAddition() {
    CNumber num1, num2, result;

    num1 = -1234;
    num2 = 567;
    result = num1 + num2;
    std::cout << "Test addition with negative (-1234 + 567): " << result.sToStr() << " (Expected: -667)" << std::endl;

    num1 = 567;
    num2 = -1234;
    result = num1 + num2;
    std::cout << "Test addition with negative (567 + -1234): " << result.sToStr() << " (Expected: -667)" << std::endl;

    num1 = -999;
    num2 = -1;
    result = num1 + num2;
    std::cout << "Test addition with both negative (-999 + -1): " << result.sToStr() << " (Expected: -1000)" << std::endl;
}

void testSubtraction() {
    CNumber num1, num2, result;

    num1 = 1234;
    num2 = 567;
    result = num1 - num2;
    std::cout << "Test subtraction (1234 - 567): " << result.sToStr() << " (Expected: 667)" << std::endl;

    num1 = 567;
    num2 = 1234;
    result = num1 - num2;
    std::cout << "Test subtraction (567 - 1234): " << result.sToStr() << " (Expected: -667)" << std::endl;

    num1 = -1234;
    num2 = 567;
    result = num1 - num2;
    std::cout << "Test subtraction (-1234 - 567): " << result.sToStr() << " (Expected: -1801)" << std::endl;

    num1 = 567;
    num2 = -1234;
    result = num1 - num2;
    std::cout << "Test subtraction (567 - (-1234)): " << result.sToStr() << " (Expected: 1801)" << std::endl;

    num1 = -567;
    num2 = -1234;
    result = num1 - num2;
    std::cout << "Test subtraction (-567 - (-1234)): " << result.sToStr() << " (Expected: 667)" << std::endl;
}

void testMultiplication() {
    CNumber num1, num2, result;

    num1 = 123;
    num2 = 45;
    result = num1 * num2;
    std::cout << "Test multiplication (123 * 45): " << result.sToStr() << " (Expected: 5535)" << std::endl;

    num1 = -123;
    num2 = 45;
    result = num1 * num2;
    std::cout << "Test multiplication (-123 * 45): " << result.sToStr() << " (Expected: -5535)" << std::endl;

    num1 = 123;
    num2 = -45;
    result = num1 * num2;
    std::cout << "Test multiplication (123 * -45): " << result.sToStr() << " (Expected: -5535)" << std::endl;

    num1 = -123;
    num2 = -45;
    result = num1 * num2;
    std::cout << "Test multiplication (-123 * -45): " << result.sToStr() << " (Expected: 5535)" << std::endl;
}

void testDivision() {
    CNumber num1, num2, result;

    num1 = 12345;
    num2 = 123;
    result = num1 / num2;
    std::cout << "Test division (12345 / 123): " << result.sToStr() << " (Expected: 100)" << std::endl;

    num1 = -12345;
    num2 = 123;
    result = num1 / num2;
    std::cout << "Test division (-12345 / 123): " << result.sToStr() << " (Expected: -100)" << std::endl;

    num1 = 12345;
    num2 = -123;
    result = num1 / num2;
    std::cout << "Test division (12345 / -123): " << result.sToStr() << " (Expected: -100)" << std::endl;

    try {
        num1 = -15355;
        num2 = 0;
        result = num1 / num2;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Test division by zero: Exception caught (Expected: Division by zero)" << std::endl;
    }
}


int main() {
    std::cout << "Running tests for CNumber class...\n" << std::endl;

    testSetFromInt();
    testAssignmentOperator();
    testAddition();
    testNegativeAddition();
    testSubtraction();
    testMultiplication();
    testDivision();

    std::cout << "\nTests completed." << std::endl;
    return 0;
}
