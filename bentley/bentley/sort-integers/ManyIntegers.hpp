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
#include <random> //random_device, std::mt19937, uniform_int_distribution
using namespace std;

class ManyIntegers {
private:
    char const * _filename; //file to operate on.
                            //"char const *" to avoid the warning of passing a string literal "filename.txt" as char *. pass it as char const * instead
    fstream _stream; //a stream is an abstraction that represents a device on which operations of input and output are performed
    unsigned int _bits; //bit-sized integers
    unsigned int _range; //range of values of integers generated
    unsigned int _num_count; //number of integers generated
    //obtain a random number from hardware
    random_device device; //save the entropy got from the operating system's entropy pool, for this process
public:
    //constructor, destructor
    ManyIntegers(char const * filename, unsigned int bits = 8);
    ~ManyIntegers();
    
    //create a file containing _n integers
    void PrepareInput();
};

#endif /* ManyIntegers_hpp */
