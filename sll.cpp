
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
        delete(pnode); //todo: Make provision to delete pnode->tdata
        count--;
        pnode = next;
    }
}

// Return the number of nodes currently in the list
template <class T>
unsigned int sllADT<T>::size() {
            return count;
}

//Insert a new node in front of the list
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


//Insert a new node at the end of the list
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
void sllADT<T>::reverse_iterative_use_stack()
{
    sllADT *pnewsll = new(sllADT<int>); 
    struct node<T>* pnode = getroot();
    struct node<T>* pnext = NULL;

    //Does not use actual stack, instead
    //utilizes insert_front to simulate stack behaviour
   
    while(pnode) {
        pnewsll->insert_front(pnode->tdata);
        pnext = pnode->next;
        delete(pnode); //todo: Make provision to delete pnode->tdata
        pnode = pnext; 
    }

    this->proot = pnewsll->getroot();
    this->plast = pnewsll->getlast();
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
T sllADT<T>::get_nth_last(unsigned int n)
{

    struct node<T>* pnode = get_nth_last_node(n);    

    return (pnode ? pnode->tdata : -1);
}

template <class T>
struct node<T>*  sllADT<T>::get_nth_last_node(unsigned int n)
{
    struct node<T>* pnode = getroot();    
    struct node<T>* pfwdnode = pnode;    
    unsigned i = 0;

    if(!n || n > size()) {
        return NULL;
    }

    // Make the pfwdnode skip first n nodes
    for(i=0; i<n && pfwdnode; i++) {
        pfwdnode = pfwdnode->next;
    }

    
    // Now pfwdnode is n node ahead,
    // and pnode is starting at the very first node
    // Forward each of the pointer one node with
    // each iteration. Doing that, when pfwdnode
    // hits the end of the list, pnode is
    // exactly pointing at nth last node
    while(pfwdnode) {
        pnode = pnode->next;
        pfwdnode = pfwdnode->next;
    }

   return pnode; 
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

template <class T>
void sllADT<T>::rotate_right(unsigned int n)
{
        unsigned int nr_nodes = size();
        struct node<T>* pnode = getroot();
        struct node<T>*pnewroot = NULL;
        struct node<T>*pnewlast = NULL;

        //calculate n mod size()
        //size() is confirmed to be non-zero, if pnode is non_NULL
        n = pnode ? n % size() : 0;  
        if(n == 0) {
                return;
        }

        for(unsigned int i=0; i < (n-1); i++) {
                pnode = pnode->next;
        }

        //We are now at the node that would become the last node - 
        //and the next node would become the new root - Keep this information
        pnewlast = pnode;
        pnewroot = pnode->next;


        //Walk to the end of the list (assume our ADT do not maintain pointer 
        //to the last node, practice that scenario)
        while(pnode->next) {
                pnode = pnode->next;
        }

        //Now we are on the very last node that currently is
        pnode->next = getroot(); //Now is no longer the last, but now points 
                                 //the fragment that begins at the current head/root 
        
        //Set the new root to what we determined earlier
        this->proot = pnewroot;

        //NULL terminate the new last-node
        pnewlast->next = NULL;

        return;    

}

template <class T>
bool sllADT<T>::is_loop()
{
    unsigned int nr_nodes = size();
    struct node<T>* pnode = NULL;
    struct node<T>* fastnode = NULL;

    if(nr_nodes == 0) {
        return false;
    }

    pnode = getroot();
    assert(pnode != NULL); //if size() returns non-zero, getroot() must 
                           //return non-null. ASSERT
    fastnode = pnode->next ? (pnode->next)->next : NULL;
    
    while(fastnode) {
        if(fastnode == pnode) {
            return true;
        }
        pnode = pnode->next;
        fastnode = fastnode->next ? (fastnode->next)->next : NULL;
    }    
    
    return false;
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

    cout << "TEST reverse_iterative_use_stack : " ;
    //Reverse the link list
    records.reverse_iterative_use_stack();

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

    
    return 0;
}

void test_get_nth_last(int max_nodes=10, int step=100, int init=500) 
{
    sllADT<int> records;
    int value = 0;
    int i = 0;


    // Insert test nodes
    for(i=0, value=init; i < max_nodes; i++) {
        records.insert_last(value);
        value += step;
        }

    cout << "TEST get_nth_last(0): ";
    assert(records.get_nth_last(0) == -1);
    cout << "PASSED" << endl;

    cout << "TEST get_nth_last(out-bounds): ";
    assert(records.get_nth_last(max_nodes+1) == -1);
    cout << "PASSED" << endl;

    cout << "TEST get_nth_last(max_nodes): ";
    assert(records.get_nth_last(max_nodes) == records.getroot()->tdata);
    cout << "PASSED" << endl;

    cout << "TEST get_nth_last(1): ";
    assert(records.get_nth_last(1) == records.getlast()->tdata);
    cout << "PASSED" << endl;

    value = init;
    for(i=0; i < max_nodes; i++) {
        cout << "TEST get_nth_last(" << max_nodes-i << "): ";
        assert(records.get_nth_last(max_nodes - i) == value);
        cout << "PASSED" << " (" << value << ")" << endl;
        value += step;
    }

}

void test_rotate_right_each(int rotatefactor, 
                            int expect_start_val,
                            int expect_max_val,
                            int max_nodes, 
                            int step, 
                            int init) 
{
    sllADT<int> records;
    struct node<int> *pnode = NULL;
    int value = 0;
    int i = 0;

    // Insert test nodes
    for(i=0, value=init; i < max_nodes; i++) {
        records.insert_last(value);
        value += step;
        }

    pnode = records.getroot();
    while(pnode) {
        //cout << pnode->tdata << endl;
        pnode = pnode->next;
    }

    records.rotate_right(rotatefactor);

    value = expect_start_val;
    pnode = records.getroot();
    while(pnode) {
        //cout << pnode->tdata << " " << value << endl;
        assert(pnode->tdata == value);
        value = (value==expect_max_val) ? init : (value+step);
        pnode = pnode->next;
    }
    
}

    
void test_rotate_right(int max_nodes=10, int step=100, int init=500) 
{
    int expect_start_val = 0; 
    int expect_max_val = 0;
    int rotatefactor=0;
    int i=0;

    expect_max_val = init + (max_nodes-1)*step;
    for(rotatefactor=0; rotatefactor < max_nodes; rotatefactor++) {
        expect_start_val = init + (rotatefactor)*step;
        cout << "test_rotate_right(" << rotatefactor << "): ";
        test_rotate_right_each(rotatefactor,
                               expect_start_val,
                               expect_max_val,
                               max_nodes,
                               step,
                               init);
        cout << "PASSED" << endl ;
    }
    for(rotatefactor=max_nodes, i=0; rotatefactor <= (max_nodes*2); rotatefactor++) {
        expect_start_val = init + (i)*step;
        cout << "test_rotate_right(" << rotatefactor << "): ";
        test_rotate_right_each(rotatefactor,
                               expect_start_val,
                               expect_max_val,
                               max_nodes,
                               step,
                               init);
        cout << "PASSED" << endl ;
        i = ++i % max_nodes;
    }
}

template <class T>
void test_is_cycle(int max_nodes=10, int step=100, int init=500) 
{
    sllADT<int> records;
    struct node<T>* proot = NULL;
    struct node<T>* second_node = NULL;
    int value = 0;
    int i = 0;

    //Test with an empty list first
    cout << "test_is_cycle: Empty list: ";
    assert(records.is_loop() == false);
    cout << "PASSED" << endl ;

    // Insert test nodes
    for(i=0, value=init; i < max_nodes; i++) {
        records.insert_last(value);
        value += step;
        }


    //Sneakily add cycle on the last node pointing back to root node
    records.getlast()->next = records.getroot();
    cout << "test_is_cycle: List with " <<  records.size() << " nodes (cycle = last->root): ";
    assert(records.is_loop() == true);
    cout << "PASSED" << endl;


    //Now remove the cycle
    records.getlast()->next = NULL;

    // Test loop without the cycle
    cout << "test_is_cycle: List with " <<  records.size() << " nodes (no cycle): ";
    assert(records.is_loop() == false);
    cout << "PASSED" << endl;

    //Sneakily add cycle on the last node pointing back to 
    //4th node (6th to the last node)  
    records.getlast()->next = records.get_nth_last_node(6);
    cout << "test_is_cycle: List with " <<  records.size() << " nodes (cycle = last->4th node): ";
    assert(records.is_loop() == true);
    cout << "PASSED" << endl;

    //Now remove the cycle (else deconstructor would spin forever)
    records.getlast()->next = NULL;
    assert(records.is_loop() == false); //Silently check if cycle has been removed successfully

    //Now make the root node point to itself
    proot = records.getroot();
    second_node = proot->next; //Memorize the original second node
    proot->next = proot;
    cout << "test_is_cycle: List with " <<  records.size() << " nodes (cycle = root->root): ";
    assert(records.is_loop() == true);
    cout << "PASSED" << endl;
    
    //Now restore the second node
    proot->next = second_node;

}
 
int main() {

    test_init();
    test_insert_front();
    test_insert_last();
    test_reverse();
    test_get_nth_last();
    test_rotate_right();
    test_is_cycle<int>();
}

