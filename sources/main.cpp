#include "decimal.h"
#include <iostream>

int main(int argc, char** argv)
{
    //Decimal o1(125), o2(2.0);
    Decimal o1, o2;
    std::cin>>o1;
    std::cin>>o2;
    std::cout<<o1*o2<<"\n"<<o1/o2<<"\n"<<o1+o2<<"\n"<<o1-o2<<"\n";
    std::cout<<(o1*100).ToDouble()<<"\n";
    return 0;
}
