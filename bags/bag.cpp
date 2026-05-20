#include "bag.h"
#include <iostream>
#include <fstream>
const std::string LOG_FILE = "BagLogFile.txt";

// Purpose: Preform an insertion sort on a itself
// Arguments: None
// Return: None
// Side effect: sorts bag it is called on
void Bag::_insertionSort() {
	for (int idx = 1; idx < _size; idx++) {
		int value = _elements[idx];
		int element = idx-1;
		while (element >= 0 && value < _elements[element]) {
			_elements[element + 1] = _elements[element];
			--element;
		}
		_elements[element+1] = value;
	}
}



// Purpose: Default constructor for bag
// Arguments: None
// Return: Bag constructed (self)
Bag::Bag() {
	_size = 0;
	_elements = nullptr;
}



// Purpose: Construct a bag, each value set to fill_arg
// Arguments: int size_arg: amount of _elements in bag
//            int fill_arg: value to set each element to
// Return: Bag constructed (self)
Bag::Bag(int size_arg, int fill_arg) {
	_size = size_arg;
	if (_size > 0) {
		_elements = new int[_size];
		for (int idx = 0; idx < _size; ++idx)
			_elements[idx] = fill_arg;
	}
	else
		_elements  = nullptr;
}



// Purpose: Construct a bag based off an array
// Arguments: int arr_arg[]: array to set the elements of the bag to
// Return: Bag constructed (self)
Bag::Bag(int arg_size, int arr_arg[]) {
	_size = arg_size;
	if (_size > 0) {
		_elements = new int[_size];
		for (int idx = 0; idx < _size; ++idx)
			_elements[idx] = arr_arg[idx];
		// ensure sorted (insertion sort)
		this->_insertionSort();
	}
	else
		_elements = nullptr;
}



// Purpose: Copy constructor
// Arguments: const Bag& bag_arg: bag to copy
// Return: Bag with copied values (self)
Bag::Bag(const Bag& bag_arg) {
	// copy size
	_size = bag_arg._size;
	// create new element list
	_elements = new int[_size];
	// copy elements
	for (int idx = 0; idx < _size; ++idx)
		_elements[idx] = bag_arg._elements[idx];
}



// Purpose: Deconstructor for bag
// Arguments: None
// Return: Deconstructed bag (self)
Bag::~Bag() {
	// zeroize
	for (int idx = 0; idx < _size; ++idx)
		_elements[idx] = 0;
	_size = 0;
	// free memory and set to nullptr
	delete[] _elements;
	_elements = nullptr;
}



// Purpose: Add an element to a bag
// Arguments: int new_element: element to add to bag
// Return: Bag with element added
Bag Bag::operator+(int new_element) const {
	bool inserted = false; // if the new element has been added
	Bag result(_size+1, 0); // result bag to return
	// open file in append mode
	std::ofstream file(LOG_FILE, std::ios::app);
	// loop through result bag
	for (int idx = 0; idx < result._size; ++idx) {
		// if the element hasn't been inserted yet
		if (!inserted) {
			// if at the end of the array or at the correct spot add new_element
			if (idx == _size || (_elements != nullptr && new_element <= _elements[idx])) {
				result._elements[idx] = new_element;
				inserted = true;
			}
			// else copy the _elements from the bag to the result bag
			else
				result._elements[idx] = _elements[idx];
		}
		// if the element has been inserted, copy elements from bag to result bag but offset by -1
		else
			result._elements[idx] = _elements[idx-1];
	}
	// log successful operation and close file
	file << "This operation: '" << *this << " + " << new_element << "' succeeded.\n";
	file.close();
	// return bag with element added
	return result;
}



// Purpose: Remove the first instance of a specific element from a b ag
// Arguments: int removed_element: element to remove
// Return: Bag with element removed
Bag Bag::operator-(int removed_element) const {
	int removed_element_idx = -1; // holds where the removed element is within the bag
	bool searching = true; // if the program is searching for where the element to remove is
	// open file in append mode
	std::ofstream file(LOG_FILE, std::ios::app);
	// find where the first instance of element to remove is
	for (int idx = 0; idx < _size && searching; ++idx) {
		if (_elements[idx] == removed_element) {
			removed_element_idx = idx;
			searching = false;
		}
	}
	// if the element to remove isn't in the bag
	if (removed_element_idx == -1) {
		// log failed operation and close file
		file << "This operation: '" << *this << " - " << removed_element << "' failed.\n";
		file.close();
		// return self
		return *this;
	}
	// If there is an element to remove
	else {
		// create a result bag
		Bag result(_size-1, 0);
		// copy the _elements of the bag, but not the element to remove
		for (int idx = 0; idx < result._size; ++idx) {
			if (idx < removed_element_idx)
				result._elements[idx] = _elements[idx];
			else
				result._elements[idx] = _elements[idx+1];
		}
		// log successful operation and close file
		file << "This operation: '" << *this << " - " << removed_element << "' succeeded.\n";
		file.close();
		// return bag with element removed
		return result;
	}
}



// Purpose: Remove a bag of elements from a bag
// Arguments: Bag& arg_bag: bag containing elements to remove
// Return: Bag with bag of elements removed
Bag Bag::operator-(Bag& arg_bag) const {
	bool remove[_size] = {false}; // bools holding which indexs of bag1 to remove
	// indexs for moving around bag1 (this) and bag2 (arg_bag)
	int bag1_idx = 0;
	int bag2_idx = 0;
	// open file in append mode
	std::ofstream file(LOG_FILE, std::ios::app);
	// find which elements in bag1 to remove
	for (bag1_idx = 0; bag1_idx < _size && bag2_idx < arg_bag._size; ++bag1_idx) {
		if (_elements[bag1_idx] == arg_bag._elements[bag2_idx]) {
			remove[bag1_idx] = true;
			++bag2_idx;
		}
	}
	// if no elements need to be removed
	if (bag2_idx == 0) {
		// log failed operation and close file
		file << "This operation: '" << *this << " - " << arg_bag << "' failed.\n";
		file.close();
		// return self
		return *this;
	}
	// if elements need to be removed
	else {
		int result_size = _size - bag2_idx; // find size of result bag
		Bag result(result_size, 0); // create result bag
		int result_idx = 0; // holds current index of result bag
		// construct result bag by only copying elements from bag1 that are not marked to be removed
		for (bag1_idx = 0; bag1_idx < _size; ++bag1_idx) {
			if (!remove[bag1_idx])
				result._elements[result_idx++] = _elements[bag1_idx];
		}
		// log successful operation and close file
		file << "This operation: '" << *this << " - " << arg_bag << "' succeeded.\n";
		file.close();
		// return result bag
		return result;
	}
}



// Purpose: Create a intersection of two bags
// Arguments: Bag& arg_bag: second bag
// Return: Intersected bags
Bag Bag::operator*(Bag& arg_bag) const {
	int bag1_idx = 0, // current index for bag1
	    bag2_idx = 0, // current index for bag2
	    result_size = 0; // size of result bag
	// open file in append mode
	std::ofstream file(LOG_FILE, std::ios::app);
	// Get the size of the result bag by looping through both bags
	while (bag1_idx < _size && bag2_idx < arg_bag._size) {
		// if the current element of bag 1 is less then the current element in bag 2 increment bag 1
		if (_elements[bag1_idx] < arg_bag._elements[bag2_idx])
			++bag1_idx;
		// if the current element of bag 1 is greater than the current element of bag 2 increment bag 2
		else if (_elements[bag1_idx] > arg_bag._elements[bag2_idx])
			++bag2_idx;
		// if the current element of bag 1 is equal to the current element of bag 2, increment both bags and result size
		else {
			++bag1_idx;
			++bag2_idx;
			++result_size;
		}
	}
	// create result bag
	Bag result(result_size, 0);
	int result_idx = 0; // current index for result bag
	// set bag indexs to beginning
	bag1_idx = 0,
	bag2_idx = 0;
	// Get the intersection (result bag) by looping through both bags
	while (bag1_idx < _size && bag2_idx < arg_bag._size) {
		// if the current element of bag 1 is less then the current element in bag 2 increment bag 1
		if (_elements[bag1_idx] < arg_bag._elements[bag2_idx])
			++bag1_idx;
		// if the current element of bag 1 is greater than the current element of bag 2 increment bag 2
		else if (_elements[bag1_idx] > arg_bag._elements[bag2_idx])
			++bag2_idx;
		// if the current element of bag 1 is equal to the current element of bag 2
		else {
			// add current bag 1 index to result b ag
			result._elements[result_idx] = _elements[bag1_idx];
			// increment all bags
			++bag1_idx;
			++bag2_idx;
			++result_idx;
		}
	}
	// log successful operation and close file
	file << "This operation: '" << *this << " * " << arg_bag << "' succeeded.\n";
	file.close();
	// Return intersection
	return result;
}



// Purpose: Create a union of two bags
// Arguments: Bag& arg_bag: second bag
// Return: Unionized bags
Bag Bag::operator/(Bag& arg_bag) const {
	int bag1_idx = 0, // current index for bag1
	    bag2_idx = 0, // current index for bag2
	    result_size = 0; // size of result bag
	// open file in append mode
	std::ofstream file(LOG_FILE, std::ios::app);
	// Get the size of the result bag by looping through both bags
	while (bag1_idx < _size && bag2_idx < arg_bag._size) {
		// if the current element of bag 1 is less then the current element in bag 2 increment bag 1 and result size
		if (_elements[bag1_idx] < arg_bag._elements[bag2_idx])
			++bag1_idx;
		// if the current element of bag 1 is greater than the current element of bag 2 increment bag 2 and result size
		else if (_elements[bag1_idx] > arg_bag._elements[bag2_idx])
			++bag2_idx;
		// if the current element of bag 1 is equal to the current element of bag 2, increment all bags
		else {
			++bag1_idx;
			++bag2_idx;
		}
		++result_size;
	}
	// since one of the bags will not reach the end, their sizes must be accounted for
	result_size += (_size - bag1_idx) + (arg_bag._size - bag2_idx);
	// create result bag
	Bag result(result_size, 0);
	int result_idx = 0; // current index for result bag
	// set bag indexs to beginning
	bag1_idx = 0,
	bag2_idx = 0;
	// Get the union (result bag) by looping through both bags
	while (bag1_idx < _size && bag2_idx < arg_bag._size) {
		// if the current element of bag 1 is less then the current element in bag 2
		if (_elements[bag1_idx] < arg_bag._elements[bag2_idx])
			// copy current element of bag 1 to result and increment
			result._elements[result_idx] = _elements[bag1_idx++];
		// if the current element of bag 1 is greater than the current element of bag 2
		else if (_elements[bag1_idx] > arg_bag._elements[bag2_idx])
			// copy current element of bag 2 to result and increment
			result._elements[result_idx] = arg_bag._elements[bag2_idx++];
		// if the current element of bag 1 is equal to the current element of bag 2
		else {
			// copy either element (bag1 is chosen but they are the same) to result bag, and increment all bags
			result._elements[result_idx++] = _elements[bag1_idx];
			++bag1_idx;
			++bag2_idx;
		}
	}
	// since one of the bags will not reach the end, their elements must be accounted for
	while (bag1_idx < _size)
		result._elements[result_idx++] = _elements[bag1_idx++];
	while (bag2_idx < arg_bag._size)
		result._elements[result_idx++] = arg_bag._elements[bag2_idx++];
	// ensure result is sorted
	result._insertionSort();
	// log successful operation and close file
	file << "This operation: '" << *this << " / " << arg_bag << "' succeeded.\n";
	file.close();
	// return result bag
	return result;
}



// Purpose: Copy one bag to another
// Arguments: const Bag& bag_arg: bag to copy
// Return: Copied bag (self)
Bag& Bag::operator=(const Bag& bag_arg) {
	// ensure that bag_arg does not equal this, because is so
	// delete[] _elements will cause errors, and extra work
	if (this == &bag_arg)
		return *this;
	// reset elements
	delete[] _elements;
	// copy size
	_size = bag_arg._size;
	// create new element array
	_elements = new int[_size];
	// copy elements
	for (int idx = 0; idx < _size; ++idx)
		_elements[idx] = bag_arg._elements[idx];
	// return copy
	return *this;
}



// Purpose: send the bag to the output stream
// Arguments: ostream& os: output stream to send to (cout)
//            const Bag &arg_bag: bag to display the elements of
// Return: ostream containing _elements of bag
std::ostream& operator<<(std::ostream& os, const Bag &arg_bag) {
	os << '{';
	// if empty set
	if (arg_bag._size == 0)
		os << "empty-set";
	// if not empty set
	else {
		for (int idx = 0; idx < arg_bag._size; ++idx) {
			os << arg_bag._elements[idx];
			if (idx < arg_bag._size-1)
				os << ", ";
		}
	}
	os << '}';
	// return output stream
	return os;
}



// Purpose: Make adding a value to a bag commutative
// Arguments: const int new_element: element to add to bag
//            const Bag& arg_bag: bag to add element to
// Return:
Bag operator+(const int new_element, const Bag& arg_bag) {
	return arg_bag + new_element;
}
