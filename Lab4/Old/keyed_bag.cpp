#include "keyed_bag.h"
#include <cassert>
#include <stdio.h>
using namespace std;
using coen79_lab4::keyed_bag;

namespace coen79_lab4 {

    //constructor
    keyed_bag::keyed_bag(){
        //initialize member variables
        //key_type keys[] = new key_type[CAPACITY];
        //data = new value_type[CAPACITY];
        bag_count = 0;

    }

    void keyed_bag::erase(){
        // Postcondition: This keyed_bag is emptied of all items and keys.
        bag_count = 0;
    }

    bool keyed_bag::erase(const key_type& key){
//     Postcondition: If key was in the keyed_bag, then the key and its value have been removed;
//     otherwise the keyed_bag is unchanged. A true return value indicates that an
//     item was removed; false indicates that nothing was removed.
        for (int i = 0; i < size(); i++) {
            if (keys[i] == key) {
                //do something
                for (int k = i; k < size(); k++) {
                    keys[k] = keys[k + 1];
                }
                for (int b = key; b < size(); b++) {
                    data[b] = data[b + 1];
                }
                bag_count--;
                return true;
            }
        }
        return false;
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key) {
//     Precondition:  size( ) < CAPACITY, and the keyed_bag does not yet contain
//     the given key.
//     Postcondition: A new copy of entry has been added to the keyed_bag with
//     the corresponding key.
        assert(size() < CAPACITY);
        for (int i = 0; i < size(); i++) {
            if (keys[i] == key) {
                printf("This key already exists.\n");
                return;
            }
        }
        data[key] = entry;
        keys[size()] = key;
        bag_count++;
        return;
    }

    void keyed_bag::operator +=(const keyed_bag& addend) {
//     Precondition:  size( ) + addend.size( ) <= CAPACITY.
//     The intersection of the keyed_bags' key tables is empty (i.e. the keyed_bags)
//     share no keys.
//     Postcondition: Each item and its key in addend has been added to this keyed_bag.
        assert(size() + addend.size()  <= keyed_bag::CAPACITY);
        for(int i = 0; i < size(); i++) {
            for(int j = 0; j < addend.size(); j++) {
                if(keys[i] == addend.keys[j]) {
                    printf("The keyed_bags share at least one key.");
                    return;
                }
            }
        }
        for(int k = 0; k < addend.size(); k++) {
            keys[size()+k] = addend.keys[k];
            data[k] = addend.data[addend.keys[k]];
            bag_count++;
        }
        return;
    }

    bool keyed_bag::has_key(const key_type& key) const {
//     Postcondition: The return value is whether or not the given key is in
//     the keyed_bag's list of keys.
        for(int i = 0; i < size(); i++) {
            if(keys[i] == key) {
                return true;
            }
        }
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
//     Precondition: has_key returns true for the given key.
//     Postcondtion: the data value corresponding to the given key is returned.
        assert(has_key(key));
        return data[key];
    }

    keyed_bag::size_type keyed_bag::size( ) const {
//     Postcondition: The return value is the total number of items in the keyed_bag.
    return bag_count;
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
//     Postcondition: The return value is number of times target is in the keyed_bag.
    keyed_bag::size_type c = 0;
    for (int i = 0; i < size(); i++) {
        if(data[i] == target) {
            c++;
        }
    }
    return c;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
//     Postcondition: The return value is true if there is at least one key used by 
//     both this bag and the "otherBag". In other words, this function checks if 
//     there is any shared key by the two bags.
    for(int j = 0; j < otherBag.size(); j++) {
        if(has_key(otherBag.keys[j])) {
            return true;
        }
    }
    return false;
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
//     Precondition:  b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY.
//                    The intersection of the keyed_bags' key tables is empty.
//                    (i.e. The two keyed_bag's have no keys in common.)
//     Postcondition: The keyed_bag returned is the union of b1 and b2.
//
    assert(b1.size() + b2.size()  <= keyed_bag::CAPACITY);
    for (int i = 0; i < b1.size(); i++) {
        for (int j = 0; j < b2.size(); j++) {
            if(b1.keys[i] == b2.keys[j]) {
                printf("The two bags have a key in common and cannot be added.\n");
                return b1; //figure what to do (maybe try-catch block)
            }
        }
    }
    keyed_bag b3;
    for(int x = 0; x < b1.size(); x++) {
        b3.keys[x] = b1.keys[x];
        b3.data[b1.keys[x]] = b1.data[b1.keys[x]];
    }
    for (int y = 0; y < b2.size(); y++) {
        b3.keys[b3.size() + y] = b2.keys[y];
        b3.data[b2.keys[y]] = b2.data[b2.keys[y]];
    }
    return b3;
    }
}