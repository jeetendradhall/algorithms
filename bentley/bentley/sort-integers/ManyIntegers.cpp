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

ManyIntegers::ManyIntegers(char const * filename, unsigned int n) : _filename(filename)/*, _stream(filename, ios::in | ios::out)*/ , _n(n) {

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

    //initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));
}

ManyIntegers::~ManyIntegers() {
    //close the file
    _stream.close();
}

//prepare the input file
void ManyIntegers::PrepareInput() {
    //write _n integers to the file
    for(int i = 0; i < _n; i++) {
        _stream << to_string(rand()) << '\n'; //endl; //writing endl forces a flush. replacing it with '\n' leaves the library to decide when to flush.
    }
}
