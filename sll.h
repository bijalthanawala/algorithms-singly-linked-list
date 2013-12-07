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
    public:
        unsigned int size();
        void insert_front(T);
        void insert_last(T);
         
};
