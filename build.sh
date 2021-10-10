#!/bin/bash
g++ -O3 -std=c++2a -c sources/decimal.cpp -o binaries/decimal.o;
g++ -O3 -std=c++2a -c sources/main.cpp -o binaries/main.o;
g++ -O3 -std=c++2a binaries/decimal.o binaries/main.o -o binaries/executable;
