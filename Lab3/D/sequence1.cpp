/*
* Names: Divya Syal & Marianne Fuyu Yamazaki Dorr
* Lab Title: Sequence
* Date: 10/13/2021
*/

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


#include "sequence1.h"
#include <cassert>
#include <cmath>


using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
	
	//constructor
	sequence::sequence() {
		//initializes member variables 
		used = 0;
		current_index = 0;
		return;
	}

    
	void sequence::start() {
		//sets the current index pointing to the first item
		current_index = 0;
		return;
	}

    
    void sequence::end() {
        //sets the current index pointing to the last item
        //checks if the sequence is empty
		assert(size() > 0);
		current_index = used - 1;
		return;
    }
    
    sequence::value_type sequence::current() const {
    	//returns the current index value
    	//checks if the current index is valid or not
		assert(current_index >= 0 && current_index < size());
		return data[current_index];
    };
    
    
    void sequence::advance() {
        //set the current index pointing to the next item
        //check: 1.if reach the end of the sequence; 2.if reach the capacity of the 'bag'
		assert(current_index < size());
		assert(current_index + 1 < sequence::CAPACITY); 
		current_index++;
		return;
    }

    bool sequence::is_item() const {
        //does the current index point to an item or not
		if (current_index < used) {
			return true;
		}
		return false;
    }
    
    
	void sequence::insert(const value_type& entry) {
		//checks capacity first
		//if the current index pointing to no item, then insert the entry at the front of the sequence
		//otherwise, shifting other items over, and insert the new entry at the current index
		//don't forget to increment the 'used' variable
		assert(size() < sequence::CAPACITY);
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
    	//checks capacity first
    	//if the current index pointing to no item, then insert the entry at the end of the sequence
		//otherwise, shifting other items over, and attach the new entry behind the current index (current_index+1)
		//don't forget to increment the 'used' variable
		assert(size() < sequence::CAPACITY);
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
    	//checks if the current index pointing to an item or not
    	//remove the current entry and shifting other items over
		assert(is_item());
		for(int i = current_index; i < used; i++) {
			data[i] = data[i + 1];
		}
		used--;
		
    }

	void sequence::insert_front(const value_type& entry) {
		//check capacity first
		//move the current index to the front and then insert
		assert(size() < sequence::CAPACITY);
		for(int i = used - 1; i >= 0; i--) {
			data[i + 1] = data[i];
		}
		current_index = 0;
		data[current_index] = entry;
		return;
	}


	void sequence::attach_back(const value_type& entry) {
		//check capacity first
		//move the current index to the end and then attach
		assert(size() < sequence::CAPACITY);
		current_index = used;
		data[current_index] = entry;
		return;
	}

	void sequence::remove_front() {
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
		//return the number of entry
		return used;
	}

    sequence::value_type sequence::operator[](int index) const {
    	//returns the value of the specific entry
    	//checks if the index is valid of not (whether has an item there)
		assert(is_item());
		return data[index];

    }
    
	sequence operator+(sequence& lhs, sequence& rhs) {
		//combines 2 sequences to 1 new sequence called result
		//checks the total capacity first
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		sequence result;
		for (int i =0; i < lhs.size(); i++) {
			result.attach_back(lhs.data[i]);
		}
		for (int i =0; i < rhs.size(); i++) {
			result.attach_back(rhs.data[i]);
		}
		return result;
	}

	sequence operator+=(sequence& lhs, sequence& rhs) {
		//attach 1 sequence to another (the first parameter)
		//checks the total capacity first
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		for (int i =0; i < rhs.size(); i++) {
			lhs.attach_back(rhs.data[i]);
		}
		return lhs;

	}


	// Homework Question Functions
	double sequence::mean() const {
		//calculates the mean of the sequence
      //const so it does not change any of the member variables, can only access/read
       assert(used!=0);
		int total = 0;
		for (int i = 0; i < used; i++) {
			total += data[i];
		}
		return (double) total/used;
		// otherwise for loop through the data array and add the values, then divide by size
	}

	double sequence::standardDeviation() const {
		//calculates the standard deviation of the sequence
      //const so it does not change any of the member variables, can only access/read
      assert(used!=0);
		double stdev = 0.0;
		for (int i = 0; i < used; i++) {
			stdev += pow((data[i]-mean()),2);
		}
		stdev/=used;
		return sqrt(stdev);
	}

	sequence::value_type summation(const sequence &s) {
		//calculates the sum of the sequence by adding up each element for instance specified
      assert(s.size()!= 0); 
		int total = 0;
		for (int i = 0; i < s.used; i++) {
			total += s.data[i];
		}
		return total;
	}

}