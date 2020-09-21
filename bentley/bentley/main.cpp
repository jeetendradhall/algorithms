//
//  main.cpp
//  bentley
//
//  Created by Sheetal on 16/09/20.
//  Copyright © 2020 jdhall. All rights reserved.
//

#include <iostream>
using namespace std;

#include "ManyIntegers.hpp"

int main(int argc, const char * argv[]) {

    //[0]
    //Rough Work: trying integer limits

    cout << "RoughWork Begin: Trying integer limits.";
    cout << "Maximum value of an int32_t: " << INT_MAX << endl;
    cout << "Maximum value produced by the rand() function: " << RAND_MAX << endl;
    cout << "Maximum value of an uint32_t: " << UINT_MAX << endl;
    cout << "Maximum value of unsigned long: " << std::numeric_limits<unsigned long>::max() << endl;
    unsigned int n = 4294967295;
    cout << "Printing an unsigned int: " << n << endl;
    cout << "RoughWork End: Trying integer limits." << endl;
    cout << "RoughWork Begin: Trying bit manipulation." << endl;
    n = 536870912;
    unsigned int pattern = 2147483648;
    for (int i = 0; i < 32; i++) {
        cout << ((n & pattern)?1:0);
        pattern = pattern >> 1;
    }
    int bits = 29;
    unsigned int range = 1;
    cout << endl << (range << bits) << endl;
    cout << "RoughWork End: Trying bit manipulation." << endl;
    
    //[1]
    //Problem: Find a missing number in a large set of numbers (Bentley - Column 2)

    ManyIntegers fiveHundredMillionInts ("500-Million-Integers.txt", bits); //create an instance of ManyIntegers
    fiveHundredMillionInts.PrepareInput(); //prepare an input file with many integers
    cout << "The missing number is: " << fiveHundredMillionInts.FindMissingNumber() << endl;

    return 0;
}
