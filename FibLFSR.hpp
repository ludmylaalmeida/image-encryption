//
// Created by ludmyla almeida on 1/31/20.
//

#ifndef UNTITLED_FIBLFSR_H
#define UNTITLED_FIBLFSR_H
#include <iostream>

class FibLFSR {
public:

    FibLFSR(std::string seed); // constructor to create LFSR with

    // the given initial seed and tap
    int step(); // simulate one step and return the new bit as 0 or 1
    int generate(int k); // simulate k steps and return k-bit integer

    // convert seed to integer
    int toInteger();

    friend std::ostream& operator<<(std::ostream& out, FibLFSR& fibLfsr);

private:
    std::string seed;
    int tap15;
    int tap13;
    int tap12;
    int tap10;
    // helper function
    bool isBinary(std::string seed);
};

#endif //UNTITLED_FIBLFSR_H
