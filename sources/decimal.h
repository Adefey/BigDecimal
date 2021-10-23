#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#pragma once

class Decimal
{
private:
    char sign;
    std::vector<int> digits;
    long int exponent;
    void RemoveZeroes();
    Decimal Inverse() const;
    int maxPrecision = 1000;
    bool IsZero() const;
    void MakeFromString(const std::string &s);
public:
    Decimal();
    Decimal(std::string str);
    Decimal(const Decimal &decimal);
    Decimal(const int &num);
    Decimal(const double &num);
    ~Decimal();
    Decimal& operator=(const Decimal &decimal);

    Decimal operator-() const;
    Decimal operator+(const Decimal &decimal) const;
    Decimal operator+=(const Decimal &decimal);
    Decimal operator-(const Decimal &decimal) const;
    Decimal operator-=(const Decimal &decimal);
    Decimal operator*(const Decimal &decimal) const;
    Decimal operator*=(const Decimal &decimal);
    Decimal operator/(const Decimal &decimal) const;
    Decimal operator/=(const Decimal &decimal);

    bool operator==(const Decimal &decimal) const;
    bool operator!=(const Decimal &decimal) const;
    bool operator<(const Decimal &decimal) const;
    bool operator<=(const Decimal &decimal) const;
    bool operator>(const Decimal &decimal) const;
    bool operator>=(const Decimal &decimal) const;

    int operator[](const int index);
    int& operator()(const int index);

    friend std::ostream& operator<<(std::ostream &out, const Decimal &decimal);
    friend std::istream& operator>>(std::istream &in, Decimal &decimal);

    int ToInt();
    double ToDouble();
};
