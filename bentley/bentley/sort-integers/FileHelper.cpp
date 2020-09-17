//
//  FileHelper.cpp
//  bentley
//
//  Created by Sheetal on 16/09/20.
//  Copyright © 2020 jdhall. All rights reserved.
//

#include "FileHelper.hpp"
#include <string>
#include <iostream>

FileHelper::FileHelper(char const * filename, unsigned int n) : _filename(filename)/*, _stream(filename, ios::in | ios::out)*/ , _n(n) {

    //open the file
    //fstream file creation fails if its instance is re-created in the member initializer list
    _stream.open(_filename);
    if (_stream.fail()) {
        cout << "ERROR: failed to create file." << endl;
        exit (0);
    }

    //initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));
}

FileHelper::~FileHelper() {
    //close the file
    _stream.close();
}

//write integers to the file
void FileHelper::WriteIntegers() {
    for(int i = 0; i < _n; i++) {
        _stream << to_string(rand()) << endl;
    }
}
