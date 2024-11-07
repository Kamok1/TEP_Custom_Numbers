#include <iostream>
#include "CNumber.h"

void testSetFromInt() {
    CNumber num;

    num = 12345;
    std::cout << "12345 -> " << num.sToStr() << " (Oczekiwane: 12345)" << std::endl;

    num = -6789;
    std::cout << "-6789 -> " << num.sToStr() << " (Oczekiwane: -6789)" << std::endl;

    num = 0;
    std::cout << "0 -> " << num.sToStr() << " (Oczekiwane: 0)" << std::endl;
}

void testAssignmentOperator() {
    CNumber num1, num2;

    num1 = 56789;
    num2 = num1;

    std::cout << "num2 = num1 -> " << num2.sToStr() << " (Oczekiwane: 56789)" << std::endl;
}

void testAddition() {
    CNumber num1, num2, result;

    num1 = 1234;
    num2 = 567;
    result = num1 + num2;
    std::cout << "1234 + 567 -> " << result.sToStr() << " (Oczekiwane: 1801)" << std::endl;

    num1 = 9999;
    num2 = 1;
    result = num1 + num2;
    std::cout << "9999 + 1 -> " << result.sToStr() << " (Oczekiwane: 10000)" << std::endl;
}

void testNegativeAddition() {
    CNumber num1, num2, result;

    num1 = -1234;
    num2 = 567;
    result = num1 + num2;
    std::cout << "-1234 + 567 -> " << result.sToStr() << " (Oczekiwane: -667)" << std::endl;

    num1 = 567;
    num2 = -1234;
    result = num1 + num2;
    std::cout << "567 + -1234 -> " << result.sToStr() << " (Oczekiwane: -667)" << std::endl;

    num1 = -999;
    num2 = -1;
    result = num1 + num2;
    std::cout << "-999 + -1 -> " << result.sToStr() << " (Oczekiwane: -1000)" << std::endl;
}

void testSubtraction() {
    CNumber num1, num2, result;

    num1 = 1234;
    num2 = 567;
    result = num1 - num2;
    std::cout << "1234 - 567 -> " << result.sToStr() << " (Oczekiwane: 667)" << std::endl;

    num1 = 567;
    num2 = 1234;
    result = num1 - num2;
    std::cout << "567 - 1234 -> " << result.sToStr() << " (Oczekiwane: -667)" << std::endl;

    num1 = -1234;
    num2 = 567;
    result = num1 - num2;
    std::cout << "-1234 - 567 -> " << result.sToStr() << " (Oczekiwane: -1801)" << std::endl;

    num1 = 567;
    num2 = -1234;
    result = num1 - num2;
    std::cout << "567 - (-1234) -> " << result.sToStr() << " (Oczekiwane: 1801)" << std::endl;

    num1 = -567;
    num2 = -1234;
    result = num1 - num2;
    std::cout << "-567 - (-1234) -> " << result.sToStr() << " (Oczekiwane: 667)" << std::endl;
}

void testMultiplication() {
    CNumber num1, num2, result;

    num1 = 123;
    num2 = 45;
    result = num1 * num2;
    std::cout << "123 * 45 -> " << result.sToStr() << " (Oczekiwane: 5535)" << std::endl;

    num1 = -123;
    num2 = 45;
    result = num1 * num2;
    std::cout << "-123 * 45 -> " << result.sToStr() << " (Oczekiwane: -5535)" << std::endl;

    num1 = 123;
    num2 = -45;
    result = num1 * num2;
    std::cout << "123 * -45 -> " << result.sToStr() << " (Oczekiwane: -5535)" << std::endl;

    num1 = -123;
    num2 = -45;
    result = num1 * num2;
    std::cout << "-123 * -45 -> " << result.sToStr() << " (Oczekiwane: 5535)" << std::endl;
}

void testDivision() {
    CNumber num1, num2, result;

    num1 = 12345;
    num2 = 123;
    result = num1 / num2;
    std::cout << "12345 / 123 -> " << result.sToStr() << " (Oczekiwane: 100)" << std::endl;

    num1 = -12345;
    num2 = 123;
    result = num1 / num2;
    std::cout << "-12345 / 123 -> " << result.sToStr() << " (Oczekiwane: -100)" << std::endl;

    num1 = 12345;
    num2 = -123;
    result = num1 / num2;
    std::cout << "12345 / -123 -> " << result.sToStr() << " (Oczekiwane: -100)" << std::endl;

    try {
        num1 = -15355;
        num2 = 0;
        result = num1 / num2;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Wyjatek" << std::endl;
    }
}


int main() {
    testSetFromInt();
    testAssignmentOperator();
    testAddition();
    testNegativeAddition();
    testSubtraction();
    testMultiplication();
    testDivision();
    return 0;
}
