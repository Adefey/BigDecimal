#include <iostream>
#pragma once

class Decimal
{
private:
    unsigned char *digitsInt;
    unsigned char *digitsFraction;
    int lengthInt;
    int lengthFraction;
public:
    Decimal(const Decimal &decimal);
    Decimal(const int &num);
    Decimal(const double &num);
    ~Decimal();
    Decimal operator=(const Decimal &decimal);

    Decimal operator+(const Decimal &decimal);
    Decimal operator+=(const Decimal &decimal);
    Decimal operator-(const Decimal &decimal);
    Decimal operator-=(const Decimal &decimal);
    Decimal operator*(const Decimal &decimal);
    Decimal operator*=(const Decimal &decimal);
    Decimal operator/(const Decimal &decimal);
    Decimal operator/=(const Decimal &decimal);

    Decimal operator==(const Decimal &decimal);
    Decimal operator!=(const Decimal &decimal);
    Decimal operator<(const Decimal &decimal);
    Decimal operator<=(const Decimal &decimal);
    Decimal operator>(const Decimal &decimal);
    Decimal operator>=(const Decimal &decimal);

    Decimal& operator[](const int index);
    Decimal& operator()(const int index);

    std::ostream& operator<<(std::ostream &out);
    std::istream& operator>>(std::istream &in);

    int ToInt();
    double ToDouble();
};
