//
// Created by ludmyla almeida on 1/31/20.
//

#include "FibLFSR.hpp"
#include <iostream>
using namespace std;

FibLFSR::FibLFSR(string seed) {

    // check if input is valid
    while(seed.length() != 16){
        cout << "The sequence of bits you entered is less than or greater than 16, try again: " ;
        cin >> seed;
    }

    while(!isBinary(seed)){
        cout << "The string you entered is not a binary number, try again: " ;
        cin >> seed;
    }

    // copy string
    this->seed = seed;
}

int FibLFSR::step() {

    int output = 0;

    // get the bits
    tap15 = seed.at(0) - '0';
    tap13 = seed.at(2) - '0';

    // XOR 15 and 13
    if((tap15 == 1 && tap13 == 1 ) || (tap15 == 0 && tap13 == 0)){
        output = 0;
    } else output = 1;

    tap12 = seed.at(3) - '0';

    // XOR 13 and 12
    if((output == 1 && tap12 == 1 ) || (output == 0 && tap12 == 0)){
        output = 0;
    } else output = 1;

    tap10 = seed.at(5) - '0';

    // XOR output and tap10
    if((output == 1 && tap10 == 1 ) || ( output == 0 && tap10 == 0)){
        output = 0;
    } else output = 1;

    // shift the string left and put the output at the LSB
    seed.erase(0,1);
    seed.push_back(output + '0');

    return output;
}

// return base 10 number
int FibLFSR::generate(int k) {

    // generate will call the step k times and return the final integer;
    int number = 0, bit = 0;

    for(int i = 0; i < k; i++){
        bit = step();
        number = number*2 + bit;
    }

    return number;
}

ostream& operator<<(ostream& out, FibLFSR& fibLfsr ){
   return out << fibLfsr.seed;
}

bool FibLFSR::isBinary(string seed){

    for(int i= 0; i < seed.length(); i++ ){
        if(isdigit(seed[i]) == false){
            return false;
        }
        else if (seed[i] == '0' || seed[i] == '1') {
            return true;
        }
    }

    return false;
}

int FibLFSR::toInteger(){

    string num = seed;
    int dec_value = 0;
    int base = 1;

    for (int i = num.length() - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;

}