/* Singly linked list */

template <class T>
struct node {
    T tdata;
    struct node *next;
};


template <class T>
class sllADT {
    private:
        unsigned int count;
        struct node<T> *proot;
        struct node<T> *plast;
    public:
        sllADT();
        ~sllADT();
        unsigned int size();
        bool insert_front(T);
        bool insert_last(T);
        void reverse_iterative_nostack();

        //Writing iterator is a big jump
        //for a C++ beginner. Handover root
        //for the driver/client to iterate by itself
        struct node<T>* getroot();
        struct node<T>* getlast();
         
};
