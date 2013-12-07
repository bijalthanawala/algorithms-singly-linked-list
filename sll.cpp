
#include <iostream>
#include <cassert>
#include "sll.h"

using namespace std;

//Constructor
template <class T>
sllADT<T>::sllADT() {
    count = 0;
    proot = NULL; 
    plast = NULL; 
}

//Destructor
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

    // If this is the first one to be inserted in the list
    // then this is also the last node in the list
    if( ! plast) {
        plast = pnewnode;
    } 

    // Bump the counter
    count++;

    return true;
}

template <class T>
bool sllADT<T>::insert_last(T datum) {

    struct node<T> *pnewnode = new(struct node<T>);

    //sanity check
    if(! pnewnode) {
        return false;
    }

    pnewnode->tdata = datum;
    
    // New node is to be inserted last hence its "next" 
    // pointer = NULL
    pnewnode->next = NULL;

    // If the list is non-empty ensure the current 
    // last one now point to this new node and
    // thus itself becomes second-last node
    if (plast) {
        plast->next = pnewnode;
    }

    //Make sure we track last node 
    plast = pnewnode;

    // If this is the first one to be inserted in the list
    // then this is also the root node in the list
    if( ! proot) {
        proot = pnewnode;
    } 

    // Bump the counter
    count++;

    return true;
}

template <class T>
void sllADT<T>::reverse_iterative_nostack()
{
    struct node<T> *a = NULL;
    struct node<T> *b = getroot();
    struct node<T> *c = b ? b->next : NULL;

    if(!b) {
        return;
    }
    
    while(b) {
        b->next = a;
        a = b;
        b = c;
        c = c ? c->next : NULL;
    }

    // Fix the 'last' and the 'root' node
    this->plast = this->proot;
    this->proot = a;
}



template <class T>
struct node<T>* sllADT<T>::reverse_node_recursively(struct node<T>*prevnode, 
                                         struct node<T>*thisnode)
{
    struct node<T> *last=NULL;  

    if(thisnode) {
        last = reverse_node_recursively(thisnode, thisnode->next);
        if(!thisnode->next)  {
                last = thisnode;
        }
        thisnode->next = prevnode;
    }

    return last; //Do not rely on ADT to maintain a last pointer, compute
}

template <class T>
void sllADT<T>::reverse_recursive()
{
    struct node<T> *root = getroot();

    if(root) {
        // Reverse the list and in the end fix root and the last pointer
        this->proot = reverse_node_recursively(NULL, root); //This routine 
                                                            //returns the very last node
        this->plast = root;
    } 

    return;
}

template <class T>
struct node<T>* sllADT<T>::getroot()
{
    return proot;
}

template <class T>
struct node<T>* sllADT<T>::getlast()
{
    return plast;
}


int test_init() 
{
    sllADT<int> init;
    cout << "TEST test_init : " ;

    assert(init.size() == 0);
    assert(init.getroot() == NULL);
    assert(init.getlast() == NULL);

    cout << "PASSED" << endl;
    
}

int test_insert_front(int max_nodes=20, int step=100, int init=500) 
{
    sllADT<int> records;
    struct node<int> *pnode = NULL;
    int value = 0;
    int i = 0;

    cout << "TEST test_insert_front : " ;

    // Insert test nodes
    for(i=0, value=init; i < max_nodes; i++) {
        // Insert test node in the front
        records.insert_front(value);

        //Ensure list's size accounts for the new node
        assert(records.size() == i+1);
        
        // Ensure the root node reflects the recent value
        // (artifact of inserting in front)
        assert(records.getroot()->tdata == value);
    
        //Make sure the last node of the list is set correctly
        if(records.size() == 1) {
            assert(records.getlast()->tdata == value);
        }

        // Next value to be inserted
        value += step;
        }

    pnode = records.getroot();
    while(pnode) {
        value -= step;
        assert(pnode->tdata == value);
        pnode = pnode->next;
    }
    
    cout << "PASSED" << endl;

    return 0;
}

int test_insert_last(int max_nodes=20, int step=100, int init=500) 
{
    sllADT<int> records;
    struct node<int> *pnode = NULL;
    int value = 0;
    int i = 0;

    cout << "TEST test_insert_last : " ;

    // Insert test nodes
    for(i=0, value=init; i < max_nodes; i++) {
        // Insert test node in the front
        records.insert_last(value);

        //Ensure list's size accounts for the new node
        assert(records.size() == i+1);
        
        // Ensure the root node reflects the recent value
        // (artifact of inserting in front)
        assert(records.getlast()->tdata == value);
    
        //Make sure the last node of the list is set correctly
        if(records.size() == 1) {
            assert(records.getroot()->tdata == value);
        }

        // Next value to be inserted
        value += step;
        }

    
    value = init;
    pnode = records.getroot();
    while(pnode) {
        assert(pnode->tdata == value);
        pnode = pnode->next;
        value += step;
    }
    
    cout << "PASSED" << endl;

    return 0;
}

bool test_reverse(int max_nodes=10, int step=100, int init=500) 
{
    sllADT<int> records;
    struct node<int> *pnode = NULL;
    int value = 0;
    int i = 0;


    // Insert test nodes
    for(i=0, value=init; i < max_nodes; i++) {
        records.insert_front(value);
        value += step;
        }

    cout << "TEST reverse_iterative_nostack : " ;

    //Reverse the link list
    records.reverse_iterative_nostack();

    // Verify each node (this automatically verifies the root node)
    value = init;
    pnode = records.getroot();
    while(pnode) {
        assert(pnode->tdata == value);
        pnode = pnode->next;
        value += step;
    }
    
    //Now verify the 'last' node
    value -= step;
    assert(records.getlast()->tdata == value); 
    
    cout << "PASSED" << endl;

    cout << "TEST reverse_recursive : " ;
    //Reverse the link list again, this time using a different method
    records.reverse_recursive();

    // Verify each node (this automatically verifies the root node)
    pnode = records.getroot();
    while(pnode) {
        assert(pnode->tdata == value);
        pnode = pnode->next;
        value -= step;
    }
    
    //Now verify the 'last' node
    value = init;
    assert(records.getlast()->tdata == value); 
    
    cout << "PASSED" << endl;

    return 0;
}



int main() {

    test_init();
    test_insert_front();
    test_insert_last();
    test_reverse();
}
