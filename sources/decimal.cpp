#include <iostream>
#include "decimal.h"

Decimal::Decimal(const Decimal &decimal)
{
     if (digitsInt)
        delete[] digitsInt;
    lengthInt=decimal.lengthInt;
    digitsInt = new unsigned char[lengthInt] {};
    for (int i=0; i<lengthInt; i++)
    {
        digitsInt[i]=decimal.digitsInt[i];
    }

    if (digitsFraction)
        delete[] digitsFraction;
    lengthFraction=decimal.lengthFraction;
    digitsFraction = new unsigned char[lengthFraction] {};
    for (int i=0; i<lengthFraction; i++)
    {
        digitsFraction[i]=decimal.digitsFraction[i];
    }
}

Decimal::~Decimal()
{
    delete[] digitsInt;
    delete[] digitsFraction;
}

Decimal Decimal::operator=(const Decimal &decimal)
{
    return Decimal(decimal);
}
