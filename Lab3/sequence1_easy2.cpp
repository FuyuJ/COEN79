//
// FILE: sequence1.cpp
//  Sequence Class
//
//  COEN 79
//  
//
//
// INVARIANT for the sequence ADT (i.e. verbalization of rules governing
//   private member function behavior):
//   1. The number of items in the sequence is in the member variable used
//      (i.e. used = 0 means the sequence is empty).
//   2. For an empty sequence, we do not care what is stored in any of the
//      array data.  For a non-empty sequence, the items in the sequence are
//      stored in strictly maintained order in data[0] through
//      data[used].  We don't care what's in the rest of data (so don't
//      need to initialize data in the constructor).
//   3. To maintain strict order, current_index is used to keep track
//      of current location in data; when current_index is used-1,
//      we're at the last place in the array.  Also whenever current_index
//      is greater than or equal to used, there is no current item.
//   4. capacity keeps track of the current capacity of the array pointed
//      to by data; capacity starts out with the value initial_capacity
//      and is changed by resize as needed (whenever used is greater than
//      or equal to capacity).
//


#include "sequence1_easy.h"

#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
	
	sequence::sequence() {
		//TO DO
		//initialize member variables here
	}

    
	void sequence::start() {
		//TO DO
		//set the current index pointing to the first item
	}

    
    void sequence::end() {
        //TO DO
        //set the current index pointing to the last item
        //don't forget to check if the sequence is empty
    }
    
    sequence::value_type sequence::current() const {
        //TO DO
    	//return the current index value
    	//don't forget to check if the current index is valid or not
    };
    
    
    void sequence::advance() {
        //TO DO
        //set the current index pointing to the next item
        //check: 1.if reach the end of the sequence; 2.if reach the capacity of the 'bag'
    }

    bool sequence::is_item() const {
        //TO DO
        //does the current index point to an item or not
    }
    Precond insert the entry at the front of the sequence
		//otherwise, shifting other items over, and insert the new entry at the current index
		//don't forget to increment the 'used' variable
	}

    
    void sequence::attach(const value_type& entry) {
    	//TO DO
    	//check capacity first
    	//if the current index pointing to no item, then insert the entry at the end of the sequence
		//otherwise, shifting other items over, and attach the new entry behind the current index (current_index+1)
		//don't forget to increment the 'used' variable
    }

    void sequence::remove_current() {
    	//TO DO
    	//check if the current index pointing to an item or not
    	//remove the current entry and shifting other items over
    	//don't forget to decrement the 'used variable'
    }

	void sequence::insert_front(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the front and then insert
	}


	void sequence::attach_back(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the end and then attach
	}

	void sequence::remove_front() {
		//TO DO
		//don't forget to check if there is an item or not
		// Move to front
	}

	sequence::size_type sequence::size() const {
		//TO DO
		//return the number of entry
	}

    sequence::value_type sequence::operator[](int index) const {
    	//TO DO
    	//return the value of the specific entry
    	//don't forget to check if the index is valid of not (whether has an item there)
    }
    
	sequence operator+(sequence& lhs, sequence& rhs) {
		//TO DO
		//combine 2 sequences to 1 new sequence
		//don't forget to check the total capacity
		assert(lhs.size() + rhs.size() <= CAPACITY);
		sequence result;
		std::copy(lhs, lhs + lhs.size(), result);
		std::copy(rhs, rhs + rhs.size(), result.size());
		return result;
	}

	sequence operator+=(sequence& lhs, sequence& rhs) {
		//TO DO
		//attach 1 sequence to another
		//don't forget to check the total capacity
		assert(lhs.size() + rhs.size() <= CAPACITY);
		std::copy(rhs, rhs + rhs.size(), lhs.size());
		return lhs;

	}


	// Homework Question Functions
	double sequence::mean() const
	{
		//TO DO
		//calculate the mean of the sequence
		return summation()/size();
		// otherwise for loop through the data array and add the values, then divide by size
	}

	double sequence::standardDeviation() const
	{
		//TO DO
		//calculate the standard deviation of the sequence
		int stdev=0;
		for (int i = 0; i < size(); i++) {
			stdev += pow((data[i]-mean()),2);
		}
		stdev/=size();
		stdev = sqrt(stdev);
	}

	sequence::value_type summation(const sequence &s)
	{
		//TO DO
		//calculate the sum of the sequence
		int total;
		for (int i = 0; i < s.size(); i++) {
			total += s.current();
		}
		return total;
	}

}