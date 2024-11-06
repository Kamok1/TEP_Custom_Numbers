#ifndef CNUMBER_H
#define CNUMBER_H
#define DEFAULT_I_LENGTH 10
#define DEFAULT_VALUE 0
#include <string>

class CNumber {
public:
    CNumber(int value = DEFAULT_VALUE);
    ~CNumber();

    CNumber(const CNumber& pcOther);

    void operator=(const CNumber& pcOther);

    void operator=(int iValue);

    CNumber operator+(const CNumber& pcOther) const;
    CNumber operator-(const CNumber& pcOther) const;
    CNumber operator*(const CNumber& pcOther) const;
    CNumber operator/(const CNumber& pcOther) const;

    bool operator<(const CNumber& pcOther) const;
    bool operator==(const CNumber& pcOther) const;

    CNumber abs() const;
    std::string sToStr() const;

    bool setNewSize(int size);

private:
    int* pi_table;
    int i_length;
    bool is_below_0;

    void setFromInt(int value);
    void removeLeadingZeros();
};

#endif
