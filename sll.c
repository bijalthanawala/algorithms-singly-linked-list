
#include <iostream>
#include <cassert>
#include "sll.h"

using namespace std;


template <class T>
sllADT<T>::sllADT() {
    count = 0;
    proot = NULL; 
}

template <class T>
sllADT<T>::~sllADT() {
    struct node<T> *pnode = proot;
    struct node<T> *next = NULL;

    while(pnode) {
        next = pnode->next;
        delete(pnode);
        count--;
        pnode = next;
    }
}

template <class T>
unsigned int sllADT<T>::size() {
            return count;
}

template <class T>
bool sllADT<T>::insert_front(T datum) {

    struct node<T> *pnewnode = new(struct node<T>);

    //sanity check
    if(! pnewnode) {
        return false;
    }

    pnewnode->tdata = datum;
    
    // Setup new node's "next" pointer
    pnewnode->next = proot;

    // This new node is the root now
    proot = pnewnode;

    // Bump the counter
    count++;

    return true;
}

template <class T>
struct node<T>* sllADT<T>::getroot()
{
    return proot;
}


int test_init() 
{
    sllADT<int> init;
    cout << "TEST test_init : " ;

    assert(init.size() == 0);
    assert(init.getroot() == NULL);

    cout << "PASSED" << endl;
    
}

int test_insert_front() 
{
    sllADT<int> records;
    struct node<int> *pnode = NULL;
    int value = 500;
    int step = 100;

    cout << "TEST test_insert_front : " ;

    records.insert_front(value);
    assert(records.size() == 1);

    value += step;
    records.insert_front(value);
    assert(records.size() == 2);

    value += step;
    records.insert_front(value);
    assert(records.size() == 3);

    value += step;
    records.insert_front(value);
    assert(records.size() == 4);

    pnode = records.getroot();
    while(pnode) {
        assert(pnode->tdata == value);
        pnode = pnode->next;
        value -= step;
    }

    
    cout << "PASSED" << endl;

    return 0;
}


int main() {

    test_init();
    test_insert_front();
}
