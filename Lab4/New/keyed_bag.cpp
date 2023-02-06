// FILE: keyed_bag.cpp
// CLASS IMPLEMENTED: keyed_bag (see keyed_bag.h for documentation)
//
//
//
//
// INVARIANT for the keyed_bag class:
//   1. The number of items in the keyed_bag is in the member variable used;
//   2. For an empty keyed_bag, we do not care what is stored in any of data; for a
//      non-empty keyed_bag the items in the keyed_bag are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.


#include <algorithm> // Provides copy function
#include <cassert>   // Provides assert function
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4
{
    const keyed_bag::size_type keyed_bag::CAPACITY;

    bool keyed_bag::erase(const key_type& key)
    {
        //find the key first
        //if cannot find, return false
        //otherwise, erase the specified item and key & decrease the used variable
        //Think about how to move other items forward to make up the deleted empty entry. (Remember you do NOT need to maintain the order of the item)
        int index = -1;
        for (int i = 0; i < size(); i++) {
            if(keys[i] == key) {
                index = i;
                break;
            }
        }
        if(index != -1) {
            for (int j = index; j < size(); j++) {
                keys[j] = keys[j+1];
                data[j] = data[j+1];
            }
            used--;
            return true;
        }
        return false;
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key)
    {
        //check the capacity and key first
        //then insert the new item in the bag
        assert(size() < CAPACITY);
        for (int i = 0; i < size(); i++) {
            if(keys[i] == key) {
                return;
            }
        }
        data[used] = entry;
        keys[used] = key;
        used++;
        return;
    }

    void keyed_bag::operator +=(const keyed_bag& addend)
    // Library facilities used: algorithm, cassert
    {
        //check the capacity and keys first
        //then combine them together
        assert(size() + addend.size() <= CAPACITY);
        if(!hasDuplicateKey(addend)) {
            for(int k = 0; k < addend.size(); k++) {
                keys[size() + k] = addend.keys[k];
                data[size() + k] = addend.data[k];
                used++;
            }
        }
        return;
    }

    bool keyed_bag::has_key(const key_type& key) const {
        //check whether a duplicate key exists or not
        for(int i = 0; i < size(); i++) {
            if(keys[i] == key) {
                return true;
            }
        }
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const {
        //check key first
        //return the item
        assert(has_key(key));
        for(int i = 0; i < size(); i++) {
            if(keys[i] == key) {
                return data[i];
            }
        }
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const
    {
        //item can be duplicated
        //this function returns the number of target items in the bag
        keyed_bag::size_type count = 0;
        for(int i = 0; i < size(); i++) {
            if(data[i] == target) {
                count++;
            }
        }
        return count;
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
    {
        //check capacity and keys first
        //return a new keyed_bag object
        assert(b1.size() + b2.size() <= CAPACITY);
        keyed_bag b3;
        b3 += b1;
        b3 += b2;
        return b3;
    }

    // Check whether the other keyed_bag shares a key with this keyed_bag.
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for(int i = 0; i < size(); i++) {
            for(int j = 0; j < otherBag.size(); j++) {
                if(keys[i] == otherBag.keys[j]){
                    return true;
                }
            }
        }
        return false;
    }
}