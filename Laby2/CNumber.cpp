#include "CNumber.h"
#include <cmath>
#include <string>


CNumber::CNumber(int value) {
    setFromInt(value);
}

CNumber::~CNumber() {
    if (pi_table) {
        delete[] pi_table;
        pi_table = 0;
    }
}

void CNumber::operator=(const int iValue) {
    setFromInt(iValue);
}

CNumber::CNumber(const CNumber& other) {
    i_length = other.i_length;
    is_below_0 = other.is_below_0;
    pi_table = new int[i_length];
    for (int i = 0; i < i_length; ++i) {
        pi_table[i] = other.pi_table[i];
    }
    removeLeadingZeros();
}

void CNumber::operator=(const CNumber& pcOther) {
    if (this == &pcOther) {
        return;  
    }

    delete[] pi_table;

    i_length = pcOther.i_length;
    is_below_0 = pcOther.is_below_0;

    pi_table = new int[i_length];
    for (int i = 0; i < i_length; ++i) {
        pi_table[i] = pcOther.pi_table[i];
    }
    removeLeadingZeros();
}


CNumber CNumber::operator+(const CNumber& pcOther) const {
    if (is_below_0 != pcOther.is_below_0) {
        return *this - pcOther.abs();
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
        int sum = carry;
        if (i >= 0) sum += pi_table[i--];
        if (j >= 0) sum += pcOther.pi_table[j--];
        result.pi_table[k--] = sum % 10;
        carry = sum / 10;
    }

    return result;
}


CNumber CNumber::operator-(const CNumber& pcOther) const {
    if (!is_below_0 && pcOther.is_below_0)
        return *this + pcOther.abs();
  
    if (is_below_0 && pcOther.is_below_0)
        return pcOther.abs() - abs();

    if (is_below_0 && !pcOther.is_below_0) {
        CNumber result = abs() + pcOther;
        result.is_below_0 = true;
        return result;
    }


    bool is_result_below_0 = false;
    const CNumber* bigger_number = this;
    const CNumber* smaller_number = &pcOther;

    if (*this < pcOther) {
        is_result_below_0 = true;
        bigger_number = &pcOther;
        smaller_number = this;
    }

    CNumber result;
    result.setNewSize(std::max(bigger_number->i_length, smaller_number->i_length));
   

    int borrow = 0;
    int i = bigger_number->i_length - 1;
    int j = smaller_number->i_length - 1;
    int k = result.i_length - 1;

    while (i >= 0 || j >= 0) {
        int sub = (i >= 0 ? bigger_number->pi_table[i--] : 0) - (j >= 0 ? smaller_number->pi_table[j--] : 0) - borrow;

        if (sub < 0) {
            sub += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }

        result.pi_table[k--] = sub;
    }

    result.is_below_0 = is_result_below_0;
    return result;
}


bool CNumber::operator<(const CNumber& other) const {
    if (is_below_0 != other.is_below_0)
        return is_below_0;

    if (!is_below_0) {
        if (i_length != other.i_length) {
            return i_length < other.i_length;
        }

        for (int i = 0; i < i_length; ++i) {
            if (pi_table[i] != other.pi_table[i]) {
                return pi_table[i] < other.pi_table[i];
            }
        }
    }

    else {
        if (i_length != other.i_length)
            return i_length > other.i_length;

        for (int i = 0; i < i_length; ++i) {
            if (pi_table[i] != other.pi_table[i]) {
                return pi_table[i] > other.pi_table[i];
            }
        }
    }

    return false;
}

CNumber CNumber::operator*(const CNumber& pcOther) const {
    int resultLength = i_length + pcOther.i_length;
    CNumber result;
    result.setNewSize(resultLength);
    result.is_below_0 = (is_below_0 != pcOther.is_below_0);

    for (int i = i_length - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = pcOther.i_length - 1; j >= 0; --j) {
            int product = pi_table[i] * pcOther.pi_table[j] + result.pi_table[i + j + 1] + carry;
            result.pi_table[i + j + 1] = product % 10;
            carry = product / 10;
        }
        result.pi_table[i] += carry;
    }

    return result;
}

CNumber CNumber::operator/(const CNumber& pcOther) const {
    CNumber dividend = abs();
    CNumber divisor = pcOther.abs();
    CNumber quotient;
    quotient.setFromInt(0);

    if (dividend < divisor) {
        return quotient; 
    }

    CNumber current(0);
    CNumber ten(10);
    CNumber one(1);

    for (int i = 0; i < dividend.i_length; ++i) {
        CNumber currentNumber;
        currentNumber.setFromInt(dividend.pi_table[i]);
        current = ((current * ten) + currentNumber);
        CNumber count(0);

        while (divisor < current || divisor == current) {
            current = current - divisor;
            count = count + one;
        }

        quotient = quotient * ten + count;
    }

    quotient.is_below_0 = (is_below_0 != pcOther.is_below_0);
    quotient.removeLeadingZeros();
    return quotient;
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

CNumber CNumber::abs() const {
    CNumber result = *this;
    result.is_below_0 = false;
    return result;
}

bool CNumber::operator==(const CNumber& other) const {
    if (i_length != other.i_length || is_below_0 != other.is_below_0)
        return false;

    for (int i = 0; i < i_length; ++i) {
        if (pi_table[i] != other.pi_table[i]) {
            return false;
        }
    }

    return true;
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

