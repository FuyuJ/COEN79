/*
* Name: Marianne Fuyu Yamazaki Dorr
* Date: 11/11/2021
* Title : Lab 7 
*/
// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        //assign private variables from passed arg
        this -> used_slots = src.used_slots;
        this -> aloc_slots = src.aloc_slots;
        this -> company_array = new company[aloc_slots];
        //copy all elements into company_array from arg
        for (int i = 0; i < used_slots; i++) {
            this -> company_array[i] = src.company_array[i];
        }

    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        //check for self-assignment
        if (this == &rhs) {
            return *this;
        }
        //release heap memory taken up by company_array to avoid memory leak
        delete [] company_array;
        //assign private variables from passed arg
        this -> used_slots = rhs.used_slots;
        this -> aloc_slots = rhs.aloc_slots;
        this -> company_array = new company[aloc_slots];
        //copy all elements into company_array
        for (int i = 0; i < used_slots; i++) {
            this -> company_array[i] = rhs.company_array[i];
        }

        return *this;
    }
    
    
    database::~database() {
        //destructor
        delete [] company_array;
        used_slots = 0;
        aloc_slots = 0;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Can't allocate less than we are using.
        
        //allocate new_capacity as size of new_array
        company *new_array = new company[new_capacity];
        //copy elements from company_array to new_array
        std::copy(company_array, company_array + used_slots, new_array);
        //release heap memory taken up by company_array
        delete [] company_array;
        //assign new_array to company_array
        company_array = new_array;
        //update aloc_slots to new_capacity
        aloc_slots = new_capacity;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        //create new_company with name entry
        company new_company(entry);
        //if there is still space in the array, add new company else reserve space and then add
        if (used_slots < aloc_slots) {
            company_array[used_slots] = new_company;
            ++used_slots;
        } else {
            reserve(used_slots + 1);
            company_array[used_slots] = new_company;
            ++used_slots;
        }
        return true;

    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        //save the index of the company if found
        size_type company_index = search_company(company);
        //if not found, return false
        if(company_index == COMPANY_NOT_FOUND){
            return false;
        }
        //otherwise, insert the product and price into the company's linked list
        return(company_array[company_index].insert(product_name, price));
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        //if company is not found, return false
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        }
        //shift elements to the left after the erased element
        for (int i = used_slots; i > company_index + 1; i--) {
            company_array[i-1] = company_array[i];
        }
        //reduce the number of used slots
        --used_slots;
        return true;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        //save the index of the company whose item needs to be erased 
        size_type company_index = search_company(cName);
        //if not found, return false
        if (company_index == COMPANY_NOT_FOUND) {
            return false;
        } 
        //if found, try to erase the product item
        //if item has been successfully erased, returns true
        //else returns false
        return company_array[company_index].erase(pName);
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        //search array for given company name and return the index 
        for(int i = 0; i < used_slots; i++) {
            if(company_array[i].get_name() == company) {
                return i;
            }
        }
        //if not found, return COMPANY_NOT_FOUND which equals -1
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
