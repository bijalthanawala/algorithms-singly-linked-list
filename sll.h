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
        void reverse_iterative_use_stack();
        struct node<T>* reverse_node_recursively(struct node<T>*prevnode, 
                                         struct node<T>*node);
        void reverse_recursive();
        void rotate_right(unsigned int n); // min n=1. If n >= count, rotates n mod count 
        void rotate_left(unsigned int n); // min n=1. If n >= count, rotates n mod count
        T get_nth_last(unsigned int n); //n is in the range 1 to count (inclusive)
        struct node<T>* get_nth_last_node(unsigned int n);
        bool is_loop();

        //Writing iterator is a big jump
        //for a C++ beginner. Handover root
        //for the driver/client to iterate by itself
        struct node<T>* getroot();
        struct node<T>* getlast();
         
};
