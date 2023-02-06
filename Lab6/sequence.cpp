/* Marianne Fuyu Yamazaki Dorr
COEN 79L: Lab 6
Node/Sequence Project
4 November 2021 */
//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    
    //Destructor
    sequence::~sequence() {
        //clear the list which will delete all the nodes
        //and reduce many_nodes to 0
        list_clear(head_ptr);
        many_nodes = 0;
    }

    void sequence::start() {
        //set cursor to head and precursor to NULL
        precursor = NULL;
        cursor = head_ptr;
    }

    void sequence::end() {
        //advance through list until the end
        while(cursor -> link() != NULL) {
            advance();
        }
    }

    void sequence::advance() {
        assert(is_item());
        //advance through list by making precursor point to where cursor is
        //and pointing cursor to it's next node.
        precursor = cursor;
        cursor = cursor -> link();

    }

    void sequence::insert(const value_type& entry) {
        //check if empty list or beginning of list
        if(!is_item() || precursor == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            if (tail_ptr == NULL) {
                tail_ptr = head_ptr;
            }
        //otherwise in middle of list
        } else {
            list_insert(precursor, entry);
            cursor = precursor -> link();
        }
        many_nodes++;
    }

    void sequence::attach(const value_type& entry) {
        //check if there is any item
        if(!is_item()) {
            //check if at beginning of list
            if(precursor == NULL) {
                list_head_insert(head_ptr, entry);
                tail_ptr = head_ptr;
                cursor = head_ptr;
            //otherwise at end of list
            } else {
                list_insert(precursor, entry);
                cursor = precursor -> link();
                tail_ptr = cursor;
            }
        //otherwise just somewhere in the middle
        } else {
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor -> link();
            //if cursor is now pointing at end, set tail to end again
            if(cursor-> link() == NULL) {
                tail_ptr = tail_ptr -> link();
            }
        }
        many_nodes++;
    }

    void sequence::operator =(const sequence& source) {
        //check for self-assignment
        if (this == &source) {
            return;
        }
        
        //clear current list
        list_clear(head_ptr);
        
        //copy data over from source into sequence list
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        cursor = head_ptr;
        many_nodes = source.many_nodes;
        //create new node that will stop once it reaches precursor of source
        node* new_precursor = source.head_ptr;
        //set precursor to head pointer so that it copies the same movements as new_precursor
        precursor = head_ptr;

        //if list is empty, set cursor to head and precursor to NULL
        if(source.precursor == NULL) {
            cursor = head_ptr;
            precursor = NULL; 
        //else, iterate through list until you reach desired precursor location
        } else {
            while(new_precursor != source.precursor) {
                new_precursor = new_precursor -> link();
                precursor = precursor -> link();
            }
            //set cursor to node after precursor if not null
            if (precursor != NULL) {
                cursor = precursor -> link();
            }
        } 
    }

    void sequence::remove_current() {
        assert(is_item());
        //if only one item at head in list
        if(precursor == NULL) {
            //set tail pointer to NULL 
            if(tail_ptr == head_ptr) {
                tail_ptr = NULL;
            }
            list_head_remove(head_ptr);
        //otherwise, multiple items in list
        } else {
            list_remove(precursor);
            cursor = precursor -> link();
            //if cursor now points to end, set tail to end
            if(cursor == NULL) {
                tail_ptr = precursor;
                return;
            }
        }
        many_nodes--; 
    }

    //CONSTANT MEMBER FUNCTIONS
    sequence::size_type sequence::size() const {
        return many_nodes;
    }

    bool sequence::is_item() const {
        return (cursor != NULL);
    }

    sequence::value_type sequence::current() const {
        assert(is_item());
        return cursor -> data();
    }
    
}