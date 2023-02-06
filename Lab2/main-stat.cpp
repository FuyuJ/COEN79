#include "statistician.h"
#include <iostream>

using namespace std;

using namespace coen79_lab2;


// Helper function to print statistician info
void printStatisticianInfo(statistician & s) {
    cout << "Sum: " << s.sum() << endl;
    cout << "Mean: " << s.mean() << endl;
    cout << "Smallest: " << s.minimum() << endl;
    cout << "Largest: " << s.maximum() << endl;
    cout << endl;
}

// main function
int main(int argc, const char * argv[])
{
    statistician s1, s2, s3;
    cout << "testing starting" <<endl;
    cout << "--- s1 prints ---" << endl;
    /*
    Positive verification
    Sum: 4.5
    Mean: 4.5
    Smallest: 4.5
    Largest: 4.5

    Sum: 0
    Mean: 0
    Smallest: -4.5
    Largest: 4.5

    Sum: 0
    Mean: 0
    Smallest: -4.5
    Largest: 4.5
    */
    s1.next(4.5);
    printStatisticianInfo(s1);
    s1.next(-4.5);
    printStatisticianInfo(s1);
    s1.next(0.0);
    printStatisticianInfo(s1);

    cout << "--- s2 prints ---" << endl;
    /*
    Positive verification
    Sum: 2.3
    Mean: 2.3
    Smallest: 2.3
    Largest: 2.3

    Sum: 3.5
    Mean: 1.75
    Smallest: 1.2
    Largest: 2.3

    Sum: -4.3
    Mean: -1.433333
    Smallest: -7.8
    Largest: 2.3
    */
    s2.next(2.3);
    printStatisticianInfo(s2);
    s2.next(1.2;
    printStatisticianInfo(s2);
    s2.next(-7.8);
    printStatisticianInfo(s2);

    s3 = s1 + s2;

    cout << "--- s3 print ---" << endl;
    /*
    Sum: -4.3
    Mean: 0.71665
    Smallest: -7.8
    Largest: 4.5
    */
    printStatisticianInfo(s3);

    cout << "--- erase prints ---" << endl;

    s1.reset();
    s1.next(5);
    printStatisticianInfo(s1);

    s2 = s1;
    printStatisticianInfo(s1);
    
    s1.reset();
    s2.reset();
    s1.next(4);
    s2.next(4);
    if (s1 == s2)
        cout << "s1 is equal to s2" << endl;

    cout << endl << "--- scaling test ---" << endl;

    s1.reset();
    s1.next(4);
    s1.next(-2);
    printStatisticianInfo(s1);
    s1 = -1 * s1;
    printStatisticianInfo(s1);

    
        

    return 0;
}
