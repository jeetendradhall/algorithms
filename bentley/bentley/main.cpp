//
//  main.cpp
//  bentley
//
//  Created by Sheetal on 16/09/20.
//  Copyright © 2020 jdhall. All rights reserved.
//

#include <iostream>
using namespace std;

#include "FileHelper.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    
    cout << "Maximum value of an int32_t: " << INT_MAX << endl;
    cout << "Maximum value produced by the rand() function: " << RAND_MAX << endl;
    cout << "Maximum value of an uint32_t: " << UINT_MAX << endl;
    
    unsigned int n = 4294967295;
    cout << "Printing an unsigned int: " << n << endl;
    
    FileHelper fourBillionInts ("four-billion-integers.txt", UINT_MAX);
    fourBillionInts.WriteIntegers();
    
    return 0;
}
