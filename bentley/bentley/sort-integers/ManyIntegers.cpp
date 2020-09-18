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
    uniform_int_distribution<int> distribution (1, _range);

    //write _n integers to the file
    for(int i = 0; i < _range; i++) {
        _stream << to_string(distribution(prnGenerator)) << '\n'; //endl; //writing endl forces a flush. replacing it with '\n' leaves the library to decide when to flush.
    }
}
