/*

week_2_program.cpp

Alex Coulson

CS260 Spring 2026 - Inst: Mitch Priestley

Purpose: Preform and display set operations on the bag class.

Specification: Create an array of bags, preform addition and subtraction 
operations to fill bags. Display the bag subtraction, union, and intersection
operations to user. 

Technical Specification: Welcome user. Create an array holding a random amount of bags. 
Fill bags in array by adding or subtracting a random number a random amount of times. 
Log each operation to file. Output bags created. Perform bag subtraction, union,
and intersection on random bags in bag array. Each time outputing the operation
and result to both the user and log file. Close all files, clear variables, sign off
and end normally.

Sources: Mitch Priestley Labs
         C++ From Control Structures Through Objects 9th Edition by Tony Gaddis

OK to share
*/
#include "bag.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

// function prototypes
void DisplayBagOperation(const int, Bag[], const char);
void FillBags(const int, Bag[]);
int RandomIntegerGenerator(const int, const int);

// declare constants
const int MIN_BAGS = 3, // minimum number of bags to generate
          MAX_BAGS = 5, // maximum number of bags to generate
          MIN_NUMBER = 0,   // minimum number contained in bags
          MAX_NUMBER = 9,  // maximum number contained in bags
          MIN_ITEMS = 1,    // minimum number of items to remove/add to bag
          MAX_ITEMS = 4,    // maximum number of items to remove/add to bag
          LOOPS = 25, // Number of addition/subtraction loops
          ADDITION_CHANCE = 70; // chance in % to preform addition
const string LOG_FILE = "BagLogFile.txt";

int main() {
	int num_Bags = 0; // number of bags in bag array
	// welcome user
	cout << "Welcome to the program\n\n";
	// get number of bags
	num_Bags = RandomIntegerGenerator(MIN_BAGS, MAX_BAGS);
	// display number of bags created to user
	cout << "We are creating " << num_Bags << " empty bags...\n";
	// create array of bags
	Bag bags[num_Bags] = {};
	// Fill bags with addition and subtraction
	cout << "Now filling bags...\n";
	FillBags(num_Bags, bags);
	// Show bag subtraction
	DisplayBagOperation(num_Bags, bags, '-');
	DisplayBagOperation(num_Bags, bags, '/');
	DisplayBagOperation(num_Bags, bags, '*');
	// clear variables
	num_Bags = 0;
	// sign off
	cout << "\nGoodbye, the program is now over.\n";
	// end normally
	return 0;
}



// Purpose: Preform and display an operation between two randomly selected bags
// Arguments: const int bag_count: number of bags in bag_arr
//            Bag bag_arr[]: array containing bags to use
//            const char operation: which operation to use (-,*,/)
// Return: None
// Side effect: Print the difference, union, or intersection of two random bags.
void DisplayBagOperation(const int bag_count, Bag bag_arr[], const char operation) {
	// get two unique random bags from bag array
	int bagA = RandomIntegerGenerator(0, bag_count-1);
	int bagB = RandomIntegerGenerator(0, bag_count-1);
	while (bagA == bagB)
		bagB = RandomIntegerGenerator(0, bag_count-1);
	Bag BagC{}; // holds result
	// output operand bags
	cout << endl << "We will now ";
	// if subtraction
	if (operation == '-') {
		cout << "subtract " << bagB << " from bag " << bagA << endl;
		BagC = bag_arr[bagA] - bag_arr[bagB];
	}
	// if intersection
	else if (operation == '*') {
		cout << "find the intersection of "  << bagB << " and " << bagA << endl;
		BagC = bag_arr[bagA] * bag_arr[bagB];
	}
	// if union
	else {
		cout << "find the union of "  << bagB << " and " << bagA << endl;
		BagC = bag_arr[bagA] / bag_arr[bagB];
	}
	// output result
	cout << "Resulting bag: The contents of the bag are as follows: " << BagC << endl;
}



// Purpose: Fill bags by randomly adding or subtracting a random amount
//          of a random number on a random bag LOOPS times
// Arguments: const int bag_count: number of bags in bag array
//            Bag bag_arr[]: array of bags to use
// Return: None
// Side effect: bag_arr bags filled with random integers from the addition and subtraction
void FillBags(const int bag_count, Bag bag_arr[]) {
	int item_value = 0;  // current value added/removed to bags
	int num_items = 0; // number of loops in the current addition/subtraction
	int current_bag = 0; // current bag having values added/removed to it
	bool adding = false; // whether the program is adding or removing items
	ofstream file(LOG_FILE, std::ios::app);
	// Add or subtract a random item a random amount of times to a random bag for LOOP loops
	for (int loop = 0; loop < LOOPS; ++loop) {
		// Find out whether the program will be adding or subtracting
		adding = (RandomIntegerGenerator(1, 100) <= ADDITION_CHANCE);
		// Generate a random item value to add/subtract
		item_value = RandomIntegerGenerator(MIN_NUMBER, MAX_NUMBER);
		// Generate how many of that item will be added/subtracted
		num_items =  RandomIntegerGenerator(MIN_ITEMS, MAX_ITEMS);
		// Find which bag to preform the operation on
		current_bag = RandomIntegerGenerator(0, bag_count-1);
		// Output to file
		file << "We will now be attempting to";
		// if adding
		if (adding) {
			// continue output
			file << " add " << num_items << ' ' << item_value << "'s to bag " << current_bag << endl;
			// // add item, num_item times to current_bag
			for (int item = 0; item < num_items; ++item)
				bag_arr[current_bag] = bag_arr[current_bag] + item_value;
		}
		// if subtracting
		else {
			// continue output
			file << " remove " << num_items << ' ' << item_value << "'s from bag " << current_bag << endl;
			// remove item, num_item times from current_bag
			for (int item = 0; item < num_items; ++item)
				bag_arr[current_bag] = bag_arr[current_bag] - item_value;
		}
	}
	// Output bags
	for (current_bag = 0; current_bag < bag_count; ++current_bag)
		cout << "Bag " << current_bag << ": " << bag_arr[current_bag] << endl;
	file.close();
}


// Purpose: to generate a random integer in the range min-max
// Arguments: int min: smallest number that can be generated
//            int max: largest number that can be generated
// Return: a random integer within range
int RandomIntegerGenerator(int min, int max) {
	static bool initialized{false};
	static mt19937 generator; // Mersenne Twister
	// Initialize the random number if not already done
	if (!initialized) {
		// Use random device to seed the generator
		random_device rd;
		generator.seed(rd());
		initialized = true;
	}
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}