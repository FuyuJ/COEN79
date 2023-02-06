/* Marianne Fuyu Yamazaki Dorr
COEN 79L: Lab 6
Node/Sequence Project
4 November 2021 */
// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>
using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor -> link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr -> link( ));
    	previous_ptr -> set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor -> link( ))
    	    if (target == cursor -> data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor -> link( ))
    	    if (target == cursor -> data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor -> link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor -> link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr -> link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr -> link( );
    	previous_ptr -> set_link( remove_ptr -> link( ) );
		
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr -> data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr -> link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr -> data( ));
    	    tail_ptr = tail_ptr -> link( );
    	    source_ptr = source_ptr -> link( );
    	}
    }

	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		
		head_ptr = NULL;
		tail_ptr = NULL;

		//Handle the case of the empty list.
		if(start_ptr == NULL || start_ptr == end_ptr) 
			return;
		
		//Make the head node for the newly created list, and put data in it.
		list_head_insert(head_ptr, start_ptr -> data());
		tail_ptr = head_ptr;

		//Copy the rest of the nodes until end_ptr one at a time, adding at the tail of new list.
		while(start_ptr -> link() != end_ptr) {
			start_ptr = start_ptr -> link();
			list_insert(tail_ptr, start_ptr -> data());
			tail_ptr = tail_ptr -> link();
			
		}
	}

	size_t list_occurrences(node* head_ptr, const node::value_type& target){
		node* cursor;
		size_t count = 0;
		cursor = head_ptr;
		
		//Handle the case of the empty list
		if (head_ptr == NULL) {
			return count; //count will be 0
		}
		//Iterate through linked list and increment count every time data 
		//is equal to target
		while (cursor != NULL) {
			if (cursor -> data() == target) {
				count++;
			}
			cursor = cursor -> link();
		}
		return count;
	}

	void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		assert(position > 0);
		assert(position <= list_length(head_ptr)+1);
		//if at start of list, insert at head
		if (position == 1) {
			list_head_insert(head_ptr, entry);
		//if at end of list, insert at end
		} else if (position == list_length(head_ptr) + 1) {
			list_insert(list_locate(head_ptr, list_length(head_ptr)), entry);
		//else, just insert regularly
		} else {
			list_insert(list_locate(head_ptr, position - 1), entry);
		}
	}

	node::value_type list_remove_at(node*& head_ptr, size_t position) {
		assert(position > 0);
		assert(position <= list_length(head_ptr));
		//store the data of node to be removed
		node::value_type new_data = list_locate(head_ptr, position) -> data();
		//if at the start of list, remove head and return data
		if(position == 1) {
			node::value_type new_data = head_ptr -> data();
			list_head_remove(head_ptr);
			return new_data;
		//otherwise, execute regular node remove function
		} else {
			list_remove(list_locate(head_ptr, position - 1));
			return new_data;
		}
	}
    
	node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		assert(1 <= start);
		assert (start <= finish);
		assert(finish <= list_length(head_ptr));
		//check for empty list
		if (head_ptr == NULL) {
			return NULL;
		}
		//initialize node for copying
		node* new_head = NULL;
		node* new_tail = NULL;
		node* start_node = list_locate(head_ptr, start);
		node* end_node = list_locate(head_ptr, finish + 1);
		list_piece(start_node, end_node, new_head, new_tail);
		return new_head;
	}

	void list_print (const node* head_ptr) {
		//check for empty list
		if (head_ptr == NULL) {
			cout << endl;
			return;
		} 
		//keep printing data from node and move head_ptr until end of list
		while (head_ptr -> link() != NULL) {
			cout << head_ptr -> data() << ", ";
			head_ptr = head_ptr -> link();
		}
		cout << head_ptr -> data() << endl;
		return;
	}

	void list_remove_dups (node* head_ptr) {
		//check for empty list
		if (head_ptr == NULL) {
			return;
		}
		//create a cursor at head_ptr
		node* cursor = head_ptr;
		//keep moving cursor until it reaches end of list
		while (cursor != NULL) {
			//create a runner that starts at cursor
			node* runner = cursor;
			//runner will go from cursor to the end of list and check if
			//there are any duplicates of cursor node
			while(runner -> link() != NULL) {
				//if duplicate, remove node containing duplicate
				if (cursor -> data() == runner -> link() -> data()) {
					node* tmp_delete = runner -> link();
					node* tmp_link = runner -> link() -> link();
					runner -> set_link(tmp_link);
					delete tmp_delete;
				} else {
					runner = runner -> link();
				}
			}
			cursor = cursor -> link();
		}
	}

	node* list_detect_loop (node* head_ptr) {
		//if no loop, return NULL
		//if loop, return head_ptr
		if (head_ptr == NULL) {
			return NULL;
		}
		//Using Floyd's Cycle Algorithm
		//node slow will move 1 node at a time
		node* slow;
		//node fast will move 2 nodes at a time
		node* fast;
		//both start at head of list
		slow = head_ptr;
		fast = head_ptr;
		//keep advancing through loop until end or if node after fast is end.
		while(fast != NULL && fast -> link() != NULL) {
			slow = slow -> link();
			fast = fast -> link() -> link();
			//if the two ever meet, then loop starting at node where slow/fast are
			if (slow == fast) {
				//reset slow to beginning of list
				slow = head_ptr;
				//progress to find location of loop
				while(slow != fast) {
					slow = slow -> link();
					fast = fast -> link();
				}
				//return start of loop
				return slow;
			}
		}
		return NULL;
	}
    
}