// FILE: rand_gen.cpp
// CLASS IMPLEMENTED: rand_gen (see rand_gen.h for documentation)
/*
* Author: Marianne Fuyu Yamazaki Dorr
* Lab Title: Pseudorandom number generator
* Date: 10/07/2021
*/

#include "random-easy.h"

namespace coen79_lab2 {
// implementations

    //Constructor
    rand_gen::rand_gen(int initial_seed, int initial_multiplier, int initial_increment, int initial_modulus) {
        assert(initial_modulus !=0);
        seed = initial_seed;
        multiplier = initial_multiplier;
        increment = initial_increment;
        modulus = initial_modulus;
        
        
    }
    
    void rand_gen::set_seed(int new_seed) {
        seed = new_seed;

    }
    
    int rand_gen::next() {
        assert(modulus !=0);
        int new_seed;
        new_seed = (multiplier * seed + increment) % modulus;
        set_seed(new_seed);
        return new_seed;
    }
    
    void rand_gen::print_info() {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
}
