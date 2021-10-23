Compiler=g++
Flags=-O3 -std=c++2a -Werror=sign-conversion -Werror=conversion -Werror=sign-compare
Product=Executable
Sources=sources/
Binaries=binaries/
Result=result/

all: $(Result)$(Product)

$(Result)$(Product): $(Binaries)decimal.o  $(Binaries)main.o
	$(Compiler) $(Flags) $(Binaries)main.o $(Binaries)decimal.o -o $(Result)$(Product)

$(Binaries)decimal.o: $(Sources)decimal.cpp $(Sources)decimal.h
	$(Compiler) $(Flags) -c $(Sources)decimal.cpp -o $(Binaries)decimal.o

$(Binaries)main.o: $(Sources)main.cpp $(Sources)decimal.h $(Binaries)decimal.o
	$(Compiler) $(Flags) -c $(Sources)main.cpp -o $(Binaries)main.o
