#include "CNumber.h"
#include <cmath>
#include <string>
#include <stdexcept>
#include <iostream>

CNumber::CNumber(int value) {
    setFromInt(value);
}

CNumber::~CNumber() {
    if (pi_table) {
        delete[] pi_table;
        pi_table = 0;
    }
}

CNumber::CNumber(const CNumber& pcOther) {
    i_length = pcOther.i_length;
    is_below_0 = pcOther.is_below_0;
    pi_table = new int[i_length];
    for (int i = 0; i < i_length; ++i) {
        pi_table[i] = pcOther.pi_table[i];
    }
    removeLeadingZeros();
}

void CNumber::operator=(const CNumber& pcOther) {
    if (this == &pcOther) return;

    delete[] pi_table;

    i_length = pcOther.i_length;
    is_below_0 = pcOther.is_below_0;

    pi_table = new int[i_length];
    for (int i = 0; i < i_length; ++i) {
        pi_table[i] = pcOther.pi_table[i];
    }
    removeLeadingZeros();
}

void CNumber::operator=(int iValue) {
    setFromInt(iValue);
}

CNumber CNumber::operator+(const CNumber& pcOther) const {
    if (is_below_0 != pcOther.is_below_0) {
        if (abs() < pcOther.abs()) {
            CNumber result = pcOther.abs() - abs();
            result.is_below_0 = pcOther.is_below_0;
            return result;
        }
        else {
            CNumber result = abs() - pcOther.abs();
            result.is_below_0 = is_below_0;
            return result;
        }
    }

    int maxLength = std::max(i_length, pcOther.i_length);
    int resultLength = maxLength + 1;

    CNumber result;
    result.setNewSize(resultLength);

    result.is_below_0 = is_below_0;

    int carry = 0;
    int i = i_length - 1;
    int j = pcOther.i_length - 1;
    int k = result.i_length - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry + (i >= 0 ? pi_table[i--] : 0) + (j >= 0 ? pcOther.pi_table[j--] : 0);
        result.pi_table[k--] = sum % 10;
        carry = sum / 10;
    }

    return result;
}

CNumber CNumber::operator-(const CNumber& pcOther) const {
    if (!is_below_0 && pcOther.is_below_0) return *this + pcOther.abs();

    if (is_below_0 && pcOther.is_below_0) return pcOther.abs() - abs();

    if (is_below_0 && !pcOther.is_below_0) {
        CNumber result = abs() + pcOther;
        result.is_below_0 = true;
        return result;
    }

    bool is_result_below_0 = false;
    CNumber bigger_number = *this;
    CNumber smaller_number = pcOther;

    if (*this < pcOther) {
        is_result_below_0 = true;
        bigger_number = pcOther;
        smaller_number = *this;
    }

    CNumber result;
    result.setNewSize(std::max(bigger_number.i_length, smaller_number.i_length));

    int borrow = 0;
    int i = bigger_number.i_length - 1;
    int j = smaller_number.i_length - 1;
    int k = result.i_length - 1;

    while (i >= 0 || j >= 0) {
        int sub = (i >= 0 ? bigger_number.pi_table[i--] : 0) - (j >= 0 ? smaller_number.pi_table[j--] : 0) - borrow;

        if (sub < 0) {
            sub += 10;
            borrow = 1;
        }
        else borrow = 0;

        result.pi_table[k--] = sub;
    }

    result.is_below_0 = is_result_below_0;
    return result;
}

CNumber CNumber::operator*(const CNumber& multiplier) const {
    int resultLength = i_length + multiplier.i_length;
    CNumber result;
    result.setNewSize(resultLength);
    result.is_below_0 = (is_below_0 != multiplier.is_below_0);

    for (int i = i_length - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = multiplier.i_length - 1; j >= 0; --j) {
            int product = pi_table[i] * multiplier.pi_table[j] + result.pi_table[i + j + 1] + carry;
            result.pi_table[i + j + 1] = product % 10;
            carry = product / 10;
        }
        result.pi_table[i] += carry;
    }

    return result;
}

CNumber CNumber::operator^(const CNumber& power) const{
    CNumber zero(0);
    if(power < zero) throw std::invalid_argument("Power smaller than 0");
    CNumber one(1);
    if(power == zero) return one;
    if (*this == zero) return zero

    CNumber result(*this);
    CNumber numerator(power);

    while ((numerator == one) == false)
    {
        result = result * (*this);
        numerator = numerator - one;
    }
    return result;
}

CNumber CNumber::operator/(const CNumber& denominator) const {
    CNumber zero(0);
    if (denominator == zero || *this == zero) throw std::invalid_argument("Division by zero");
    CNumber numerator = abs();
    CNumber denominatorAbs = denominator.abs();
    CNumber result;
    result.setFromInt(0);

    if (numerator < denominatorAbs) return result;

    CNumber currentValue(0);
    CNumber ten(10);
    CNumber one(1); 

    for (int i = 0; i < numerator.i_length; ++i) {
        CNumber currentDigit;
        currentDigit.setFromInt(numerator.pi_table[i]);
        currentValue = ((currentValue * ten) + currentDigit);
        CNumber count(0);
        while (denominatorAbs < currentValue || denominatorAbs == currentValue) {
            currentValue = currentValue - denominatorAbs;
            
            count = count + one;
        }

        result = result * ten + count;
    }

    result.is_below_0 = (is_below_0 != denominator.is_below_0);
    result.removeLeadingZeros();
    return result;
}


bool CNumber::operator<(const CNumber& pcOther) const {
    if (is_below_0 != pcOther.is_below_0) return is_below_0;

    if (!is_below_0) {
        if (i_length != pcOther.i_length) return i_length < pcOther.i_length;

        for (int i = 0; i < i_length; ++i) {
            if (pi_table[i] != pcOther.pi_table[i]) return pi_table[i] < pcOther.pi_table[i];
        }
    }

    else {
        if (i_length != pcOther.i_length)  return i_length > pcOther.i_length;

        for (int i = 0; i < i_length; ++i) {
            if (pi_table[i] != pcOther.pi_table[i]) {
                return pi_table[i] > pcOther.pi_table[i];
            }
        }
    }

    return false;
}

bool CNumber::operator==(const CNumber& pcOther) const {
    if (i_length != pcOther.i_length || is_below_0 != pcOther.is_below_0) return false;

    for (int i = 0; i < i_length; ++i) {
        if (pi_table[i] != pcOther.pi_table[i]) return false;
    }

    return true;
}


CNumber CNumber::abs() const {
    CNumber result = *this;
    result.is_below_0 = false;
    return result;
}

std::string CNumber::sToStr() const {
    std::string result;
    int i = 0;

    while (i < i_length && pi_table[i] == 0) {
        i++;
    }

    if (i == i_length) return "0";
    if (is_below_0) result += "-";
    for (int j = i; j < i_length; ++j) {
        result += std::to_string(pi_table[j]);
    }

    return result;
}

bool CNumber::setNewSize(int size) {
    if (size <= 0) return false;
    int* newTable = new int[size]();
    int copyLength = std::min(size, i_length);
    for (int i = 0; i < copyLength; ++i) {
        newTable[i] = pi_table[i];
    }

    delete[] pi_table;
    pi_table = newTable;
    i_length = size;
    return true;
}

void CNumber::setFromInt(int value) {
    delete[] pi_table;

    is_below_0 = value < 0;
    value = std::abs(value);

    int temp = value;
    i_length = (temp == 0) ? 1 : 0;
    while (temp > 0) {
        temp /= 10;
        i_length++;
    }

    pi_table = new int[i_length]();

    for (int i = i_length - 1; i >= 0 && value > 0; --i) {
        pi_table[i] = value % 10;
        value /= 10;
    }
}

void CNumber::removeLeadingZeros() {
    int leadingZeros = 0;
    while (leadingZeros < i_length && pi_table[leadingZeros] == 0) {
        leadingZeros++;
    }

    if (leadingZeros == i_length) {
        i_length = 1;
        delete[] pi_table;
        pi_table = new int[i_length]();
    }
    else if (leadingZeros > 0) {
        int newLength = i_length - leadingZeros;
        int* newTable = new int[newLength];
        for (int i = 0; i < newLength; ++i) {
            newTable[i] = pi_table[i + leadingZeros];
        }
        delete[] pi_table;
        pi_table = newTable;
        i_length = newLength;
    }
}
