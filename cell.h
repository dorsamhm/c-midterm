#pragma once
#include "genome.h"
class cell:protected genome
{
protected:
    int cromozomeCount;
    genome* gene;
public:
    void getCromozome(int cromozomes);
    void cellDie();
    void bigMutate(string s1, int n, string s2, int m);
    void smallMutate(char a, char c, int n, int m);
    void reverseMutate(string s1, int n);
    void printPalindrom();
    void print();
    int getCromozomeCount();
};


