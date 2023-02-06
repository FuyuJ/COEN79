#include "random-easy.h"
#include <iostream>

using namespace std;
using namespace coen79_lab2;

// Main Functions

void printNumbers(rand_gen &r, int num) {

    for (int i = 0; i < num; i++) {
        r.print_info();
        cout << "Next: " << r.next() << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    rand_gen rg(1, 40, 725, 729);

    printNumbers(rg, 5);
    
    rg.set_seed(1);
    printNumbers(rg, 5);
    
    rg.set_seed(15);
    printNumbers(rg, 5);


    rand_gen rg2(14, 85, 637, 1947);
    
    printNumbers(rg2, 5);
    
    rg2.set_seed(14);
    printNumbers(rg2, 5);
    
    cout << "testing starting" <<endl;
    /*
     Positive verification
     Rg(3, 4, 5, 6)
     = (3 * 4 + 5) % 6
      = 5
     Now seed = 5
     = (3 * 5 + 5) % 6
      = 2
     Now seed = 2
     = (3 * 2 + 5) % 6
     = 5
     So on and so forth
    */
    rand_gen rg3(3, 4, 5, 6);
    printNumbers(rg3, 5);

    /*
     Negative verification
     Rg(3, 4, 5, -6)
     = (3 * 4 + 5) % -6
     = (17 mod -6)
     = 5 (continue with the same pattern)

     Rg(3, -4, 5, 6)
     = (3 * -4 + 5) % 6
      = (-7 mod 6)
     = -1

     Rg(3, -4, 5, -6)
     = (3* -4 + 5) % -6
     = (-7 mod -6)
     = -1
    */
    rand_gen rg4(3, 4, 5, -6);
    printNumbers(rg4, 3);
    
    rand_gen rg5(3, -4, 5, 6);
    printNumbers(rg5, 3);
    
    rand_gen rg6(3, -4, 5, -6);
    printNumbers(rg6, 3);

    /*
     Edge case
     Rg(3, 4, 5, 0)
     = (3*4 + 5) % 0
     Returns error

     Rg(3, 0, 0, 6)
     = (3*0 + 0) % 6
     = 0 % 6
     = 0
    */
    rand_gen rg7(3, 4, 5, 1);
    printNumbers(rg7, 3);
    
    rand_gen rg8(3, 0, 0, 6);
    printNumbers(rg8, 3);

    return 0;
}
