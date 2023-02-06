/* Divya Syal
COEN 79L: Lab 4
Polynomial Porject
14 October 2021 */

#include "poly.h"
#include <cassert>
#include <cmath>
#include <climits>

/*
Invariant: 
*/


using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
	
	
    polynomial::polynomial(double c, unsigned int exponent) {
//     CONSTRUCTOR for the polynomial class
//     PRECONDITION: exponent <= MAXIMUM_DEGREE
//     POSTCONDITION: This polynomial has been created with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.
        assert(exponent <= MAXIMUM_DEGREE);
        // poly data array has default value of 0?
        clear();
        poly[exponent] = c; //  will use default values of 0 and 0.0 if not specified

    }

    void polynomial::update_current_degree() {
//     POSTCONDITION: The current degree is set to the highest exponent
//      with a non-zero coeficient.
        current_degree = degree(); 

    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
//     PRECONDITION: exponent <= MAXIMUM_DEGREE.
//     POSTCONDITION: Sets the coefficient for exponent
        assert(exponent <= polynomial::MAXIMUM_DEGREE);
        poly[exponent] = coefficient;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
//     PRECONDITION: exponent <= MAXIMUM_DEGREE.
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
        assert(exponent <= polynomial::MAXIMUM_DEGREE);
        poly[exponent] += amount;

    }
    
    void polynomial::clear() {
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            poly[i] = 0;
        }
    }



    polynomial polynomial::antiderivative() const {
//     PRECONDITION: degree( ) < MAXIMUM_DEGREE
//     POSTCONDITION: The return value is the antiderivative (indefinite integral)
//     of this polynomial.
//     NOTE: The return polynomial always has a constant term of zero.
        // loop again from end of the array, can't store integral of term with maximum degree though
        assert(degree() < polynomial::MAXIMUM_DEGREE);
        polynomial result;
        result.poly[0] = 0; 
        // stating at 0, loop up to 2nd last index and apply reverse chain rule at each to get antiderivative                             
        for (int i = 0; i < MAXIMUM_DEGREE; i++) {   
           result.poly[i+1] = (poly[i]/(i+1));
        }
        return result;

    }

    double polynomial::coefficient(unsigned int exponent) const {
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//     NOTE: For exponents > MAXIMUM_DEGREE, the return value is always zero.
        if (exponent > MAXIMUM_DEGREE) { return 0; }
        return poly[exponent];
    }


    double polynomial::definite_integral(double x0, double x1) const {
//     POSTCONDITION: Returns the value of the definite integral computed from
//     x0 to x1.  The answer is computed analytically.
        int larger = 0.0;
        int smaller = 0.0;
        
        polynomial result = antiderivative(); // first get the antriderivative polynomial object 
        // antiderivative function will never have a nonzero value in the MAXIMUM_DEGREE slot,so we skip that 
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            // evaluate value of each term for both parameters, adding the result to either "larger" or "smaller"
            larger += result.poly[i]*pow(x1, i);
            smaller += result.poly[i]*pow(x0, i);
        }
        return larger-smaller;
    }

    unsigned int polynomial::degree() const {
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero (even
//     though, technically, this polynomial does not have a degree).
        // start at max index, cycle down to 0th index, return the current index if the coefficient there is nonzero
        for (int i = MAXIMUM_DEGREE; i >= 0; i--) {
            if (poly[i] != 0) {
                return i;
            }
        }
        return 0; // return 0 for zero polynomial
    }

    polynomial polynomial::derivative() const {
//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.
        polynomial result;
        // start at the 1st index, cycle up to max index, utilizing chain rule to set the coefficients
        //  of the derivative
        for (int i = 1; i < MAXIMUM_DEGREE; i++) {       
            result.poly[i-1] = (poly[i] * i);               
        }
        return result;

    }

    double polynomial::eval(double x) const {
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
        int result = 0.0;
        // loop through eap index of poly data array and multiply ocefficient by value specified
        //  to the i-th power, which is then added to variable result 
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE+1; i++) {
            result += (poly[i])*pow(x, i);
        }
        return result;
    }


    bool polynomial::is_zero() const {
//     POSTCONDITION: The return value is true if and only if the polynomial
//     is the zero polynomial.
    // ASSUMING ZERO POLYNOMIAL IS ALL 0 COEFFICIENT
        // starting at 0 index, loop up till max index, returning false if nonzero coefficient found
        for (int i = 0; i < polynomial::MAXIMUM_DEGREE +1; i++) { 
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
        for (int i = e+1; i < MAXIMUM_DEGREE +1; i++) { 
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
        for (int i = e -1; i >= 0; i--) {
            if (poly[i] != 0) {
                return i;
            }
        }
        return UINT_MAX;
    }

    // CONSTANT OPERATORS for the polynomial class
    double polynomial::operator() (double x) const {
//     Same as the eval member function.
        return eval(x); 
    }


    
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
//      POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.
        polynomial result;
        // cycle through each index of the poly arrays starting at 0 as set the coefficient based on
        //  addition of parameters' coefficients at specified index
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            result.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        return result;

    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.
        polynomial result;
        // cycle through each index of the poly arrays starting at 0 and set coefficient based on 
        //  substraction of the parameters' coefficients at specified index
        for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            result.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        return result;
     
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
//      PRECONDITION: p1.degree( ) + p2.degree( ) <= MAXIMUM_DEGREE.
//      POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//      and the answer is the sum of all these term-by-term products.
//      For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//      return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial result;
        // only cycle through the highest degree of each polynomial reference parameter
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
        for (int i = polynomial::MAXIMUM_DEGREE; i >= 0; i--) {
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