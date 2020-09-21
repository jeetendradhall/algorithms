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

enum class Child {None, Left, Right};

class ManyIntegers {
private:
    const int INTEGER_BIT_SIZE = 32;
    string _filename; //file to operate on.
                            //"char const *" to avoid the warning of passing a string literal "filename.txt" as char *. pass it as char const * instead
    unsigned int _bits; //bit-range of integers
    unsigned int _range; //range of values of integers generated
    unsigned int _num_count; //number of integers generated
    //obtain a random number from hardware
    random_device device; //save the entropy got from the operating system's entropy pool, for this process
public:
    //constructor sets the input filename and bit range
    //it calls CalculateRangeAndQuantity() to calculate numeric range and number of integers to be generated
    ManyIntegers(string filename, unsigned int bits = 8);

    //create a file containing _num_count integers
    void PrepareInput();

    //find the missing number in the range 1.._range
    unsigned int FindMissingNumber ();

private:
    //calculate numeric range and number of integers to be generated
    void CalculateRangeAndQuantity ();
    //open file in a given mode, exit if fails
    void FileOp(string filename, fstream& stream, ios::openmode mode, char const * operation);
    //traverse down the partitions looking for the missing number
    unsigned int Split (string filename_parent, unsigned int lower_bound, unsigned int upper_bound);
};

#endif /* ManyIntegers_hpp */
