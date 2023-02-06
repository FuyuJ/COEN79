/* Marianne Fuyu Yamazaki Dorr
COEN 79L: Lab 5
Polynomial Project
29 October 2021 */

#include "poly.h"
#include <cassert>
#include <cmath>
#include <climits>

/*
Invariant: The poly class has a private member variable unsigned int size that 
            keeps track of the current size of the dynamic array. A pointer to a
            double array poly which contains the coefficients of the polynomial and
            an unsigned int current_degree which keeps track of which degree we're 
            currently at. 
*/


using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5 {
	
//CONSTRUCTORS	
    polynomial::polynomial(double c, unsigned int exponent) {
    //POSTCONDITION: This polynomial has been created with all zero
    //coefficients, except for coefficient c for the specified exponent.
    //When used as a default constructor (using default values for
    //both arguments), the result is a polynomial with all zero
    //coefficients.
        
        //if exponent is less then MAXIMUM_DEGREE then use MAXIMUM_DEGREE as length of array
        if(exponent < MAXIMUM_DEGREE) {
            poly = new double[MAXIMUM_DEGREE];
            //assign all coefficients to 0
            for (int i = 0; i < MAXIMUM_DEGREE; i++) {
                poly[i] = 0;
            }
            //set size to MAXIMUM_DEGREE
            size = MAXIMUM_DEGREE; 
        //if exponent is > MAXIMUM_DEGREE, instantiate a new poly[] of length exponent + 1
        } else {
            poly = new double[exponent + 1];
            //assign all coefficients to 0
            for (int i = 0; i < (exponent + 1); i++) {
                poly[i] = 0;
            }
        }
        if (c > 0) {
            poly[exponent] = c;
            current_degree = exponent;
        } else {
            current_degree = 0;
        }    
    }
    polynomial::polynomial(const polynomial& source) {
        //POSTCONDITION: This polynomial has been created as a copy of the source
        poly = new double[source.size];
        size = source.size;
        current_degree = source.current_degree;
        copy(source.poly, source.poly+size, poly);
    }

    polynomial::~polynomial(){
        //Destructor
        delete [] poly;
    }
//HELPER FUNCTIONS
    void polynomial::update_current_degree() {
    //POSTCONDITION: The current degree is set to the highest exponent
    //with a non-zero coeficient.
        for (int i = current_degree; i < size; i++) {
            if (poly[i] != 0) {
                current_degree = i;
            }
        }

    }

//MODIFICATION MEMBER FUNCTIONS

    void polynomial::reserve(size_t number) {
        //create a new double array
        double *larger_poly;

        if(number <= size) 
            return; //the allocated memory is already the right size or can't be reduced
        
        //allocate array of length number to larger_poly
        larger_poly = new double[number];
        //copy over the data from current array to larger poly
        copy(poly, poly+size, larger_poly);
        //delete poly
        delete [] poly;
        //assign larger_poly to poly
        poly = larger_poly;
        //for everything else, assign 0
        for (int i = size; i < number; i++) {
            poly[i] = 0;
        }
        //set size equal to number
        size = number;
    }

    void polynomial::trim(){
        
        if(size == current_degree) {
            return; //already at minimum memory space
        }
        //create new double array
        double *smaller_poly;
        //allocate smaller_poly to length of private member variable size
        smaller_poly = new double[size];
        //copy coefficients from poly to smaller_poly
        copy(poly, poly+size, smaller_poly);
        //delete poly
        delete [] poly;
        //assign smaller_poly to poly
        poly = smaller_poly;
        return;
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
//     POSTCONDITION: Sets the coefficient for exponent
        if (exponent < size) {
            poly[exponent] = coefficient;
        } else {
            reserve(exponent + 1);
            poly[exponent] = coefficient;
        }
        //for adding down
        if(poly[exponent] == 0) {
            current_degree = 0;
            for (unsigned int i = 0; i < size; i++) {
                if (poly[i] != 0) {
                    current_degree = i;
                }
            }
        }
        if (exponent > current_degree && poly[exponent] != 0){
            current_degree = exponent;
        } 
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
        if (exponent < size) {
            poly[exponent] += amount;
        } else {
            reserve(exponent + 1);
            poly[exponent] += amount;
        }
        //for adding down
        if (poly[exponent] == 0) {
            current_degree = 0;
            for (unsigned int i = 0; i < size; i++) {
                if(poly[i] != 0) 
                    current_degree = i;
            }
        }
        if (exponent > current_degree && poly[exponent] != 0) {
            current_degree = exponent;
        } 
    }
    
    void polynomial::clear() {
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
        for (int i = 0; i < size; i++) {
            poly[i] = 0;
        }
        current_degree = 0;
    }

//MODIFICATION OPERATOR for the polynomial class
    polynomial& polynomial::operator =(const polynomial& source) {
        //if polynomial is trying to copy from itself, then simply return
        if (&source == this) 
            return *this;
        
        //if size is not equal to size of source, delete poly and reallocate 
        //poly as double of length source.size
        if (size != source.size) {   
            delete []poly;
            poly = new double[source.size];
            size = source.size;
        }
        //set current_degree equal to source.current_degree
        current_degree = source.current_degree;
        //copy coefficients from source.poly to poly
        copy(poly, poly+size, source.poly );
        //return current instantiated object (this)
        return *this;
    }

    polynomial& polynomial::operator=(double c){
    //POSTCONDITION: This polynomial is set to the polynomial with only the
    //constant term c. The other coefficients (for x, x^2, x^3...) are all zero.
        poly[0] = c;
        for (int i = 1; i < size; i++) {
            poly[i] = 0;
        }
        return *this;
    }

//CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative() const {
//     POSTCONDITION: The return value is the antiderivative (indefinite integral)
//     of this polynomial.
//     NOTE: The return polynomial always has a constant term of zero.
        polynomial result;
        result.assign_coef(0, 0); 
        // stating at 0, loop up to 2nd last index and apply reverse chain rule at each to get antiderivative                             
        for (int i = 0; i < size; i++) {   
            result.assign_coef(poly[i]/(i+1), (i + 1));
        }
        result.current_degree = current_degree +1;
        return result;

    }

    double polynomial::coefficient(unsigned int exponent) const {
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
        if (exponent > current_degree) { return 0; }
        return poly[exponent];
    }


    double polynomial::definite_integral(double x0, double x1) const {
//     POSTCONDITION: Returns the value of the definite integral computed from
//     x0 to x1.  The answer is computed analytically.
        int larger = 0.0;
        int smaller = 0.0;
        
        polynomial result = antiderivative(); // first get the antriderivative polynomial object 
        // antiderivative function will never have a nonzero value in the MAXIMUM_DEGREE slot,so we skip that 
        for (int i = 0; i < size; i++) {
            // evaluate value of each term for both parameters, adding the result to either "larger" or "smaller"
            larger += result.poly[i]*pow(x1, i);
            smaller += result.poly[i]*pow(x0, i);
        }
        return larger-smaller;
    }

    polynomial polynomial::derivative() const {
//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.
        polynomial result;
        // start at the 1st index, cycle up to max index, utilizing chain rule to set the coefficients
        //  of the derivative
        if (current_degree == 0) {
            result.current_degree = 0;
            result.poly[0] = 0;
        } else {
            for (int i = 1; i < size; i++) {  
                result.assign_coef((poly[i]*i), i-1);                   
            }
        }
        result.current_degree = current_degree - 1;
        return result; 
        

    }

    double polynomial::eval(double x) const {
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
        double result = 0.0;
        // loop through each index of poly data array and multiply ocefficient by value specified
        //  to the i-th power, which is then added to variable result 
        for (int i = 0; i <= current_degree; i++) {
            if (i == 0) {
                result += poly[0];
            } else {
                result += poly[i] * pow(x, i);
            }
        }
        return result;
    }


    bool polynomial::is_zero() const {
//     POSTCONDITION: The return value is true if and only if the polynomial
//     is the zero polynomial.
    // ASSUMING ZERO POLYNOMIAL IS ALL 0 COEFFICIENT
        // starting at 0 index, loop up till max index, returning false if nonzero coefficient found
        for (int i = 0; i < size +1; i++) { 
            if (poly[i] != 0) {
                return false;
            }
        }
        // no nonzero coefficients found, success
        return true;
    }


    unsigned int polynomial::next_term(unsigned int e) const {
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.
        // starting at index speicified and looping up to max index, return index if it has nonzero coefficient
        for (int i = (e + 1); i < size; i++) { 
            if (poly[i] != 0) {
                return i;
            }
        }
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
        // starting at index speicified and looping down to 0th index, return index if it has nonzero coefficient
        if (e == 0) {
            return UINT_MAX;
        }
        if (e > size)
            e = size;
        for (int i = e -1; i >= 0; i--) {
            if (poly[i] != 0) {
                return i;
            }
        }
        return UINT_MAX;
    }
    
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
//      POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.
        int new_size;
        if (p1.current_size() > p2.current_size()) { 
            new_size = p1.current_size();
        } else {
            new_size = p2.current_size();
        }
        
        polynomial result;
        // cycle through each index of the poly arrays starting at 0 as set the coefficient based on
        //  addition of parameters' coefficients at specified index
        for (int i = 0; i <= new_size; i++) {
            result.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        return result;
       // cycle through each index of the poly arrays starting at 0 as set the coefficient based on
        //  addition of parameters' coefficients at specified index

    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.
        int new_size;
        if (p1.current_size() > p2.current_size()) { 
            new_size = p1.current_size();
        } else {
            new_size = p2.current_size();
        }
        polynomial result;
        // cycle through each index of the poly arrays starting at 0 and set coefficient based on 
        //  substraction of the parameters' coefficients at specified index
        for (int i = 0; i <= new_size; i++) {
            result.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        return result; 
     
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
//      POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//      and the answer is the sum of all these term-by-term products.
//      For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//      return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//
        
        polynomial result;
        // cycle through each index of the poly arrays starting at 0 and set coefficient based on 
        //  substraction of the parameters' coefficients at specified index
        for (int i = 0; i <= p1.degree(); i++) {
            for (int j = 0; j <= p2.degree(); j++) {
                // have to use "add_to_coeff"becuase the degree porducts can be the same 
                result.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j);
            }
        }
        return result;
    }

    std::ostream& operator << (std::ostream& out, const polynomial& p) {
//      POSTCONDITION: The polynomial has been printed to ostream out, which,
//      in turn, has been returned to the calling function.
//      The format of the polynomial when printed should be as follows:
//              -2.5x^2 - 4x + 5.9
//      1) There should be exactly 1 space between the numbers and the operators.
//      2) The constant coeficient should be printed by itself: 5.3, not 5.3x^0
//      3) The first coeficient chould be followed by a plain x: 4x, not 4x^1
//      4) The highest degree's coeficient should have a sign: -2.5x^2, but the
//          following values should all be separated by appropriate operators
//          and then printed unsigned: -2.5x^2 - 4x...
//      5) If you manipulate any settings of the outstream inside of this,
//          such as the precision, they should be restored to what they were
//          at the start of the function before returning.
//

        // if you have a zero polynomail, print out 0.0
        if (p.is_zero()) {
            out << "0.0" << endl;
            return out;
        }    
        
        int count = 0;
        // loop through the data array from highest possible degree to lowest (constant), printing each nonzero term as specified above
        for (int i = p.current_size(); i >= 0; i--) {
            if (p.coefficient(i) != 0) {
                count++;
                // if you are not on first nonzero coefficient, seperate out the operator
                if (count > 1) {
                  // check if value is negative, if so, surround minus sign with spaces
                  if (p.coefficient(i) < 0) {
                      out << " - "; 
                  } else {
                      // positive value, surround plus sign with spaces
                      out << " + ";
                  }
                  out << abs(p.coefficient(i)); // print out absolute value of value
                
                } else {
                  // it is your first nonzero value so print out coefficient, with sign attached 
                  out << p.coefficient(i);
                }
                
                // only print "x" if not at zero index (constant)
                if (i > 0) {
                    out << "x";
                }
                
                // only print the power if the power is greater than 1
                if (i > 1) {
                    out << "^" << i;
                }
            }
        }
        out << endl;  // new line
        return out;
    }
}