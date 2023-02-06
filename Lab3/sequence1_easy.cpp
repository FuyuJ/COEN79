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
	
	//constructor
	sequence::sequence() {
		//TO DO
		//initialize member variables here
		used = 0;
		current_index = 0;
		return;
	}

    
	void sequence::start() {
		//TO DO
		//set the current index pointing to the first item
		current_index = 0;
		return;
	}

    
    void sequence::end() {
        //TO DO
        //set the current index pointing to the last item
        //don't forget to check if the sequence is empty
		current_index = used - 1;
		return;
    }
    
    sequence::value_type sequence::current() const {
        //TO DO
    	//return the current index value
    	//don't forget to check if the current index is valid or not
		assert(current_index >= 0 && current_index < used);
		return data[current_index];
    };
    
    
    void sequence::advance() {
        //TO DO
        //set the current index pointing to the next item
        //check: 1.if reach the end of the sequence; 2.if reach the capacity of the 'bag'
		assert(current_index < used);
		assert(current_index + 1 < sequence::CAPACITY); 
		current_index++;
		return;
    }

    bool sequence::is_item() const {
        //TO DO
        //does the current index point to an item or not
		if (current_index < used) {
			return true;
		}
		return false;
    }
    
    
	void sequence::insert(const value_type& entry) {
		//TO DO
		//check capacity first
		//if the current index pointing to no item, then insert the entry at the front of the sequence
		//otherwise, shifting other items over, and insert the new entry at the current index
		//don't forget to increment the 'used' variable
		assert(used < sequence::CAPACITY);
		if (!is_item()){
			for (int i = used; i > 0; i--) {
				data[i] = data[i-1];
			}
			data[0] = entry;
		} else {
			for (int j = used; j > current_index; j--) {
				data[j] = data[j-1];
			}
			data[current_index] = entry;
		}
		used++;
		return;
	}

    
    void sequence::attach(const value_type& entry) {
    	//TO DO
    	//check capacity first
    	//if the current index pointing to no item, then insert the entry at the end of the sequence
		//otherwise, shifting other items over, and attach the new entry behind the current index (current_index+1)
		//don't forget to increment the 'used' variable
		assert(used < sequence::CAPACITY);
		if(!is_item()) {
			data[used] = entry;
		} else {
			for(int i = used - 1; i > current_index; i--) {
				data[i + 1] = data[i];
			}
			data[current_index + 1] = entry;
		}
		used++;
		return;
    }

    void sequence::remove_current() {
    	//TO DO
    	//check if the current index pointing to an item or not
    	//remove the current entry and shifting other items over
    	//don't forget to decrement the 'used variable'
		if(!is_item()) {
			return;
		} else {
			for(int i = current_index; i < used; i++) {
				data[current_index] = data[current_index + 1];
			}
			used--;
		}
    }

	void sequence::insert_front(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the front and then insert
		assert(used < sequence::CAPACITY);
		for(int i = used - 1; i >= 0; i--) {
			data[i + 1] = data[i];
		}
		current_index = 0;
		data[current_index] = entry;
		return;
	}


	void sequence::attach_back(const value_type& entry) {
		//TO DO
		//check capacity first
		//move the current index to the end and then attach
		assert(used < sequence::CAPACITY);
		current_index = used;
		data[current_index] = entry;
		return;
	}

	void sequence::remove_front() {
		//TO DO
		//don't forget to check if there is an item or not
		// Move to front
		current_index = 0;
		assert(is_item());
			for(int i = used - 1; i >= 0; i--){
				data[i - 1] = data[i];
			}
		used--;
	}

	sequence::size_type sequence::size() const {
		//TO DO
		//return the number of entry
		return used;
	}

    sequence::value_type sequence::operator[](int index) const {
    	//TO DO
    	//return the value of the specific entry
    	//don't forget to check if the index is valid of not (whether has an item there)
		if(!is_item()) {
			return NULL;
		} else {
			return data[index];
		}

    }
    
	sequence operator+(sequence& lhs, sequence& rhs) {
		//TO DO
		//combine 2 sequences to 1 new sequence
		//don't forget to check the total capacity
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		sequence result;
		for (int i =0; i < lhs.size(); i++) {
			result.attach_back(lhs.data[i]);
		}
		for (int i =0; i < rhs.size(); i++) {
			result.attach_back(rhs.data[i]);
		}
		/*
		std::copy(lhs.data, lhs.data + lhs.size(), result.data);
		std::copy(rhs.data, rhs.data + rhs.size(), result.size());
		*/
		return result;
	}

	sequence operator+=(sequence& lhs, sequence& rhs) {
		//TO DO
		//attach 1 sequence to another
		//don't forget to check the total capacity
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		for (int i =0; i < rhs.size(); i++) {
			lhs.attach_back(rhs.data[i]);
		}
		//std::copy(rhs.data, rhs.data + rhs.size(), lhs.size());
		return lhs;

	}


	// Homework Question Functions
	double sequence::mean() const
	{
		//TO DO
		//calculate the mean of the sequence
		int total;
		for (int i = 0; i < used; i++) {
			total += data[i];
		}
		return (double) total/used;
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