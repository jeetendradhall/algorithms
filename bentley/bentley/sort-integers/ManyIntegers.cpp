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

ManyIntegers::ManyIntegers(char const * filename, unsigned int bits) : _filename(filename)/*, _stream(filename, ios::in | ios::out)*/ , _bits(bits) {

    //calculate range
    _range = 1 << bits;

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

    //open the file
    //fstream file creation fails if its instance is re-created in the member initializer list
    _stream.open(_filename, ios::out);
    if (_stream.fail()) { //file already exists, delete and recreate
        cout << "WARNING: deleting existing file..." << endl;
        if (remove(_filename) != 0) { //delete
            cout << "ERROR: failed to delete existing file." << endl;
            exit (0);
        } else {
            _stream.open(_filename, ios::out); //recreate
            if (_stream.fail()) {
                cout << "ERROR: failed to create file." << endl;
                exit (0);
            }
        }
    }
}

ManyIntegers::~ManyIntegers() {
    //close the file
    _stream.close();
}

//prepare the input file
void ManyIntegers::PrepareInput() {
    //prepare a uniform distribution for a given range
    //https://diego.assencio.com/?index=6890b8c50169ef45b74db135063c227c
    
    //seed the PRNG (Pseudo Random Number Generator)
    //PRNG: "Mersenne Twister" based on the Mersenne prime 2^19937−1)
    mt19937 prnGenerator (device());
    //create a uniform distribution for a given range
    uniform_int_distribution<int> distribution (1, _range); //closed interval, boundary values 1 and _range included

    //write _range integers to the file
    for(int i = 0; i < _num_count; i++) {
        _stream << to_string(distribution(prnGenerator)) << '\n'; //endl; //writing endl forces a flush. replacing it with '\n' leaves the library to decide when to flush.
    }
}
