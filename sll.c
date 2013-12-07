#include <iostream>
#include "sll.h"
using namespace std;


template <class T>
sllADT<T>::sllADT() {
    count = 0;
    proot = NULL;
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


int main() 
{
    sllADT<int> records;
    struct node<int> *pnode = NULL;

    cout << "Initial size = " << records.size() << endl;
    records.insert_front(100);
    cout << "size after inserting (100) = " << records.size() << endl;
    records.insert_front(200);
    cout << "size after inserting (200) = " << records.size() << endl;
    records.insert_front(300);
    cout << "size after inserting (300) = " << records.size() << endl;
    records.insert_front(400);
    cout << "size after inserting (400) = " << records.size() << endl;

    pnode = records.getroot();
    while(pnode) {
        cout << pnode->tdata << endl;
        pnode = pnode->next;
    }

    
    return 0;
}
