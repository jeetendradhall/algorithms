//
//  ManyIntegers.cpp
//  bentley
//
//  Created by Sheetal on 16/09/20.
//  Copyright © 2020 jdhall. All rights reserved.
//

#include "ManyIntegers.hpp"
#include <string> //to_string(), compare(), c_str()
#include <iostream> //cout, srand(), rand() (cstdlib included via iostream)
#include <stdio.h> //remove()

//constructor sets the input filename and bit range
//it calls CalculateRangeAndQuantity() to calculate numeric range and number of integers to be generated
ManyIntegers::ManyIntegers(string filename, unsigned int bits) : _filename(filename), _bits(bits) {
    CalculateRangeAndQuantity();
}

//##### private functions #####

//calculate numeric range and number of integers to be generated
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

//open file in a given mode, exit if fails
void ManyIntegers::FileOp(string filename, fstream& stream, ios::openmode mode, char const * operation) {
    stream.open(filename, mode);
    if(stream.fail()) {
        cout << "ERROR: failed to " << operation << " file " << filename << endl;
        exit (0);
    }
}

//traverse down the partitions looking for the missing number
unsigned int ManyIntegers::Split (string fn_parent, unsigned int lower_bound, unsigned int upper_bound) {
    
    //create left and right children files
    string fn_left("left.txt"), fn_right("right.txt");
    fstream left, right;
    FileOp(fn_left, left, ios::out, "create");
    FileOp(fn_right, right, ios::out, "create");

    //mid point (top of the lower partition)
    unsigned int mid_lower = lower_bound + (upper_bound - lower_bound - 1)/2; //e.g. 16+(31-16-1)/2 = 16+(15-1)/2 = 16+7 = 23. the partitions are [16..23][24..31]
    unsigned int leftCount = 0, rightCount = 0; //count number of left and right children

    //read the parent file
    fstream parent;
    FileOp(fn_parent, parent, ios::in, "read");
    string in_str; //line read as string
    while (getline(parent, in_str)) {
        unsigned int in_int = stoi(in_str); //string read is converted to integer
        if (in_int <= mid_lower) {
            left << in_str << '\n'; //write number to the left child file
            leftCount++;
        } else {
            right << in_str << '\n'; //write number to the right child file
            rightCount++;
        }
    }

    //close the file handles to prepare for deletion and  subsequent treatment as input
    parent.close();
    left.close();
    right.close();

    //delete the parent file (only if it is not the original input file)
    if(_filename.compare(fn_parent) != 0) {
        //delete the parent file
        if (remove(fn_parent.c_str()) != 0)
            cout << "WARNING: Could not remove intermediate file " << fn_parent <<
            " with bounds " << lower_bound << " and " << upper_bound << endl;
    }

    //found a missing number?
    if (leftCount == 0) {
        return lower_bound;
    } else if (rightCount == 0) {
        return mid_lower + 1; //can return upper_bound too
    } else {
        //left or right child to be renamed as parent
        string fn_parent_inner("parent.txt");
        
        //have one of the children as the new parent, and delete the other child
        unsigned int half_partition_size = (upper_bound - lower_bound + 1)/2; //e.g. (31-16+1)/2 = (15+1)/2 = 8
        //if left child has count up to half partition size, go down the left child
        if (leftCount < half_partition_size) {
            //delete the right child file
            if (remove(fn_right.c_str()) != 0)
                cout << "WARNING: Could not remove right child file " << fn_right <<
                " with bounds " << mid_lower + 1 << " and " << upper_bound << endl;
            //go down the left child
            rename(fn_left.c_str(), fn_parent_inner.c_str()); //rename left child file as parent
            return Split(fn_parent_inner, lower_bound, mid_lower);
        } else { //go down the right child
            //delete the left child file
            if (remove(fn_left.c_str()) != 0)
                cout << "WARNING: Could not remove left child file " << fn_left <<
                " with bounds " << lower_bound << " and " << mid_lower << endl;
            //go down the left child
            rename(fn_right.c_str(), fn_parent_inner.c_str()); //rename right child file as parent
            return Split(fn_parent_inner, mid_lower + 1, upper_bound);
        }
    }
}

//##### public functions #####

//create a file containing _num_count integers
void ManyIntegers::PrepareInput() {
    //file object to create the input file
    fstream stream;
    FileOp(_filename, stream, ios::out, "create");

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

//find the missing number in the range 1.._range
unsigned int ManyIntegers::FindMissingNumber () {
    return Split(_filename, 1, _range);
}
