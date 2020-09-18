//
//  ManyIntegers.hpp
//  bentley
//
//  Created by Sheetal on 16/09/20.
//  Copyright © 2020 jdhall. All rights reserved.
//

#ifndef ManyIntegers_hpp
#define ManyIntegers_hpp

#include <fstream>
using namespace std;

class ManyIntegers {
private:
    char const * _filename; //file to operate on.
                            //"char const *" to avoid the warning of passing a string literal "filename.txt" as char *. pass it as char const * instead
    fstream _stream; //a stream is an abstraction that represents a device on which operations of input and output are performed
    unsigned int _n; //size of date to be read or written
public:
    //constructor, destructor
    ManyIntegers(char const * filename, unsigned int n = UINT_MAX);
    ~ManyIntegers();
    
    //create a file containing _n integers
    void PrepareInput();
};

#endif /* ManyIntegers_hpp */
