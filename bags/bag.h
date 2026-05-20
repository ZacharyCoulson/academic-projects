/*
Class Name: Bag

Description: This class represents a bag (aka a multiset). The class has two
member variables. The max size of the elements that can be contained in the bag,
and the elements contained in the bag. Insertion sort, sorts itself. The bag
can be constructed by filling each element in a user specified size with a user 
specified integer. A bag can also be constructed by copying elements of an integer 
array into a bag. This class also allows copy construction. This class contains a 
destructor which will zeroize all elements and free all memory. The size of any bag
can be received by using the getBag accessor. The bag class allows the set operators
of addition (+), subtraction w/ integer (-), substraction w/ bag (-), intersection 
(*), and union(/). Finally the class allows for output in roster notation to the 
output stream using the stream insertion operator. 

Sources: Mitch Priestley Labs
         C++ From Control Structures Through Objects 9th Edition by Tony Gaddis
         Discrete Mathematics and its Applications 8th Edition by Kenneth H. Rosen
         Chat with chatGPT checking for edge cases
         Sorting algorithm - programiz 
*/
#ifndef BAG_H
#define BAG_H

#include <iostream>

class Bag {
    protected:
        int _size;
        int* _elements;
        void _insertionSort();
    public:
        Bag(); 
        Bag(int, int);
        Bag(int, int[]);
        Bag(const Bag&);
        ~Bag();
        int getSize() { return _size; }
        Bag operator+(int) const;
        Bag operator-(int) const;
        Bag operator-(Bag&) const;
        Bag operator*(Bag&) const;
        Bag operator/(Bag&) const;
        Bag& operator=(const Bag&);
        friend std::ostream& operator<<(std::ostream& , const Bag&);
        friend Bag operator+(const int, const Bag&);
};

#endif

