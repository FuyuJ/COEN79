/*
* Name: Marianne Fuyu Yamazaki Dorr
* Date: 11/11/2021
* Title : Lab 7 
*/
// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"
#include "node.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        this -> company_name = company_name;
        this -> head_ptr = NULL;
        this -> tail_ptr = NULL;
    }
    
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        //copy linked list from src to head_ptr with tail_ptr assigned to the end
        list_copy(src.head_ptr, head_ptr, tail_ptr);
        company_name = src.company_name;
    }

    
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        //check for self-assignment
        if (this == &src) return *this;
        //clear current list
        list_clear(this -> head_ptr);
        //copy src list into this
        list_copy(src.head_ptr, this -> head_ptr, this -> tail_ptr);
        company_name = src.company_name;
        return *this;

    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            //add the new product at the head
            head_ptr = new node(product_name, price, NULL);
            tail_ptr = head_ptr;
        }
        else {
            //check if name already exists
            node* cursor = head_ptr;
            while (cursor != NULL) {
                //if it does, return false
                if(cursor -> getName() == product_name) {
                    return false;
                }
                cursor = cursor -> getLink();
            }
            //else insert the new product and its price to the end of the list
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }
    
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        //search for the product name and point cursor to it
        node* cursor = list_search(head_ptr, product_name);
        //if cursor is not null, copy data from head_ptr to erased element and delete head
        if(cursor != NULL) {
            cursor ->setName(head_ptr -> getName());
            cursor ->setPrice(head_ptr -> getPrice());
            list_head_remove(head_ptr);
            return true;
        }
        return false;
    }
    
    
}
