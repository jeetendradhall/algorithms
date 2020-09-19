//
//  ManyIntegers.cpp
//  bentley
//
//  Created by Sheetal on 16/09/20.
//  Copyright © 2020 jdhall. All rights reserved.
//

#include "ManyIntegers.hpp"
#include <string> //to_string()
#include <iostream> //cout, srand(), rand() (cstdlib included via iostream)
#include <stdio.h> //remove()

ManyIntegers::ManyIntegers(char const * filename, unsigned int bits) : _filename(filename), _bits(bits) {
    CalculateRangeAndQuantity();
}

void ManyIntegers::CalculateRangeAndQuantity() {
    //calculate range
     _range = 1 << _bits;

     //calculate the number of numbers to generate
     //this should be lower than range, the maximum power of 10 with the leading digit same as the leading digit of range
     //what power of 10 can the range accommodate?
     int ten_exponent = floor(log10(_range));
     //what is the value of that power of 10 number?
     unsigned int ten_power = pow(10, ten_exponent);
     //what is the leading digit of the range?
     int leading_digit = floor(_range/ten_power);
     //get closer to _range by having the same leading digit as range
     _num_count = ten_power * leading_digit;
}

//prepare the input file
void ManyIntegers::PrepareInput() {
    //file object to create the input file
    fstream stream;
    stream.open(_filename, ios::out);
    if (stream.fail()) {
        cout << "ERROR: failed to create file." << endl;
        exit (0);
    }

    //prepare a uniform distribution for a given range
    //https://diego.assencio.com/?index=6890b8c50169ef45b74db135063c227c
    
    //seed the PRNG (Pseudo Random Number Generator)
    //PRNG: "Mersenne Twister" based on the Mersenne prime 2^19937−1)
    mt19937 prnGenerator (device());
    //create a uniform distribution for a given range
    uniform_int_distribution<int> distribution (1, _range); //closed interval, boundary values 1 and _range included

    //write _range integers to the file
    for(int i = 0; i < _num_count; i++) {
        stream << to_string(distribution(prnGenerator)) << '\n'; //endl; //writing endl forces a flush. replacing it with '\n' leaves the library to decide when to flush.
    }
}

//find the missing number
unsigned int ManyIntegers::FindMissingNumber() {

    //file object to read the original input file
    fstream original_input_file;
    original_input_file.open(_filename, ios::in);
    if (original_input_file.fail()) {
        cout << "ERROR: failed to open file " << _filename << endl;
        exit (0);
    }
    
    //set the input file to be read
    fstream& input_file = original_input_file;

    //file object to read/write the left child
    fstream left_child;
    left_child.open("left_child.txt", ios::in|ios::out);
    if (left_child.fail()) {
        cout << "ERROR: failed to open left_child.txt" << endl;
        exit (0);
    }
    
    //file object to read/write the right child
    fstream right_child;
    right_child.open("right_child.txt", ios::in|ios::out);
    if (right_child.fail()) {
        cout << "ERROR: failed to open right_child.txt" << endl;
        exit (0);
    }

    //make log n passes over
    for(int i = INTEGER_BIT_SIZE; i >= 0; i--) {
        //set the bit to be tested for this pass
        //split the input across 0 and 1 bit into two different files
        //find which file has at the most half the numbers
        //set that file as the input file (optionally, delete the other file)
    }

    return 0;
}
