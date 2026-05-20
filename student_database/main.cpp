/*
3/3 PARTS COMPLETE 

Alex Coulson
Week 9 Program
CS162 Winter 2026, Mitch Priestley 
Purpose: Sort & Search a database of testers
Specification: Load data from a sequential text file into an array of testers.
               While reading in get the amount of testers read, this will be 
               used to indicate the portion of the testers array to search/sort.
               Display all testers within the array. Allow user to search for 
               a tester based off their name using a linear search. Display the 
               result of the search. If the tester is found output their data,
               else output that no matching tester was found. Preform a 
               selection sort on the array based on score. Display array again.
               Allow user to search for a tester based on score. Use a binary
               search to find the student. Display outcome of search. Preform
               a bubble sort on the array based on name. Display array again.
               Allow user to search for a tester based on name. Use a binary
               search to do so. Display the outcome of the search. Display 
               the testers with the minimum and maximum score of the dataset.
               Wrap up by clearing all variables. Output a sign off message. 
               Finally end normally by returning 0. 
Sources: C++ From Control Structures Through Objects 9th Edition by Tony Gaddis
		 CS162 Labs - Mitch Priestley 
		 Search & Sorting algorithms - programiz 
OK to share
*/
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Tester.h"

using namespace std;

// Declare constants
const unsigned short int MAX = 100; // Used as a maximum size of the array
const string FILENAME = "Scores.txt";

// Function prototypes
bool isAllAlpha(string str);
unsigned short int loadData(Tester tester[]);
unsigned short int PromptScore();
short int BinarySearch(const Tester arr[], const unsigned short int size,
                       const unsigned short int target);
short int BinarySearch(const Tester arr[], const unsigned short int size,
                       const string target);
short int LinearSearch(const Tester arr[], const unsigned short int size,
                       const string target);
string PromptName();
void BubbleSort(Tester arr[], const unsigned short int size);
void DisplayAll(const Tester arr[], const unsigned short int size);
void DisplayMinMax(const Tester arr[], const unsigned short int size);
void OutputSearch(const Tester arr[], short int idx);
void SelectionSort(Tester arr[], const unsigned short int size);
void Swap(Tester &a, Tester &b);


int main() {
	Tester testers[MAX] {};
	unsigned short int size {0}; // used to track the # of people
	short int idx {0}; // index of found tester
	// Part 1
	cout << "welcome to the Tester Program!\n";
	size = loadData(testers);
	DisplayAll(testers, size);
	idx = LinearSearch(testers, size, PromptName());
	OutputSearch(testers, idx);
	// part 2
	SelectionSort(testers, size);
	DisplayAll(testers, size);
	idx = BinarySearch(testers, size, PromptScore());
	OutputSearch(testers, idx);
	// part 3
	BubbleSort(testers, size);
	DisplayAll(testers, size);
	idx = BinarySearch(testers, size, PromptName());
	OutputSearch(testers, idx);
	DisplayMinMax(testers, size);
	// Wrap up
	idx = size = 0;
	cout << "\nGoodbye, the program is now over.\n";
	return 0;
}



// Purpose: Check if a string only contains alphabetic characters
// Parameters: const string str: string to check
// Return: Bool - Returns false if anu non alphabetic character is found,
//                else returns true
bool isAllAlpha(const string str) {
	bool allChars = true;
	for (size_t chr = 0; chr < str.length() && allChars; ++chr) {
		if (!isalpha((str[chr])))
			allChars = false;
	}
	return allChars;
}



// Purpose: Write data from a file into an array of testers
// Parameters: Tester tester[]: array of testers to populate
// Return: unsigned short int - Number of testers written into the array
unsigned short int loadData(Tester tester[]) {
	unsigned short int dataCount = 0, // counter variable of the data, is returned
    score = 0;                        // score and name read from
	string name;                      // file to be stored in array
	// Open sequential file for writing
	fstream infile (FILENAME, ios::in);
	// Make sure file exists and has opened properly
	if (!infile.is_open()) {
		cout << "Error! File was not found: " << FILENAME << endl;
		exit(1);
	}
	// Read data into the array until the array is full or the eof
	do {
		// read data from file
		infile >> name >> score >> ws;
		if (infile) {
			tester[dataCount].set_name(name);
			tester[dataCount].set_score(score);
			++dataCount; // increment data counter
		}
	} while(dataCount < MAX && !infile.eof());
	// return count of data
	return dataCount;
}



// Purpose: Get a score (0-100) from the user
// Parameters: None
// Return: Valid Score (0-100)
unsigned short int PromptScore() {
	bool invalid = true; // Becomes false once user enters a valid input
	unsigned short int input; // Score input from the user
	// Prompt user for an input until the user enters a valid input
	do {
		cout << "Please enter the score to search for: ";
		cin >> input;
		// If cin fails (e.g. user has entered the wrong datatype), reset cin
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "ERROR! cin has failed,"
			     << " make sure you enter a non-negative integer.\n";
		}
		else {
			// If the score is too big
			// (to small doesn't need to be checked on unsigned)
			if (input > 100) {
				cin.ignore(1024, '\n');
				cout << "ERROR! Invalid score, must be 0-100.\n";
			}
			// If the user has entered a valid input
			else
				invalid = false;
		}
	} while(invalid);
	// Return the validated user input
	return input;
}



// Purpose: Preform a binary search on an array of testers, searching by score
// Parameters: const Tester arr[]: array of testers to search
//             const unsigned short int size: amount of array to search
//             const unsigned short int target: score to find
// Return: Index of tester with matching score to target, or -1 if not found
short int BinarySearch(const Tester arr[], const unsigned short int size,
                       const unsigned short int target) {
	short int left = 0,
	          middle = 0,
	          right = size - 1;
	unsigned short int value;
	while (left <= right) {
		middle = left + (right - left) / 2;
		value = arr[middle].get_score();
		if (target == value)
			return middle;
		if (target > value)
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;
}



// Purpose: Preform a binary search on an array of testers, searching by name
// Parameters: const Tester arr[]: array of testers to search
//             const unsigned short int size: amount of array to search
//             const string target: name to find
// Return: Index of tester with matching name to target, or -1 if not found
short int BinarySearch(const Tester arr[], const unsigned short int size,
                       const string target) {
	unsigned short int left = 0,
	                   middle = 0,
	                   right = size - 1;
	string value;
	while (left <= right) {
		middle = left + (right - left) / 2;
		value = arr[middle].get_name();
		if (target == value)
			return middle;
		if (target > value)
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;
}



// Purpose: Preform a linear search on an array of testers, searching by name
// Parameters: const Tester arr[]: array of testers to search
//             const unsigned short int size: amount of array to search
//             const string target: name to find
// Return: Index of tester with matching name to target, or -1 if not found
short int LinearSearch(const Tester arr[], const unsigned short int size,
                       const string target) {
	for (int idx = 0; idx < size; idx++)
		if (arr[idx].get_name() == target)
			return idx;
	return -1;
}



// Purpose: Get a name (3-7 alphabetical chars) from user
// Parameters: None
// Return: Valid name
string PromptName() {
	bool invalid = true; // Becomes false once user enters a valid input
	string input; // Name input from the user
	// While the user hasn't entered a valid name, ask user for a name
	do {
		cout << "Please enter the name to search for: ";
		cin >> input;
		// if cin failed (e.g. wrong data type)
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "ERROR! cin has failed, make sure you enter a name.\n";
		}
		// if cin was successful
		else {
			// check name is not too short or long, and that the name
			// is all alphabetic characters
			if (input.length() < 3 || input.length() > 7
			                       || (!isAllAlpha(input))) {
				cin.ignore(1024, '\n');
				cout << "ERROR! Must be 3-7 alphabetic characters long.\n";
			}
			// if the user has entered a valid name, exit do while loop
			else
				invalid = false;
		}
	} while(invalid);
	// Return valid name from user
	return input;
}



// Purpose: Preform a bubble sort on an array of testers, sorting by name ascending
// Parameters: Tester arr[]: array to sort
//             const unsigned short int size: portion of array to sort (indexs 0 to size-1)
// Return: None
void BubbleSort(Tester arr[], const unsigned short int size) {
	// Loop through until sorted
	for (int pass = 0; pass < size - 1; ++pass) {
		// loop through each tester
		for (int tester = 0; tester < size - pass - 1; ++tester)
			// compare, swap if comparision is true
			if (arr[tester].get_name() > arr[tester + 1].get_name()) {
				Swap(arr[tester], arr[tester+1]);
			}
	}
}



// Purpose: Display all testers within an array of testers
// Parameters: const Tester arr[]: array to output
//             const unsigned short int size: portion of array to output
// Return: None
void DisplayAll(const Tester arr[], const unsigned short int size) {
	cout << setw(10) << left << "NAME" << setw(6) << right << "SCORE" << endl;
	for (unsigned short int tester = 0; tester < size; tester++)
		arr[tester].output(cout);
	cout << endl;
}



// Purpose: Display the minimum and maximum scores from a tester array
//          (assumes is sorted by score)
// Parameters: const Tester arr[]: array to output from
//             const unsigned short int size: portion of array with data,
//                                            used to find lowest score
// Return: None
void DisplayMinMax(const Tester arr[], const unsigned short int size) {
	cout << "---HIGHEST SCORE---" << endl;
	arr[0].output(cout);
	cout << "----LOWEST SCORE---" << endl;
	arr[size-1].output(cout);
}



// Purpose: Output the result of a binary search
// Parameters: const Tester arr[]: holds a potential tester to output
//             short int idx: index of the tester to output, or -1 if not
// Return: None
void OutputSearch(const Tester arr[], short int idx) {
	if (idx != -1)  {
		arr[idx].output(cout);
		cout << endl;
	}
	else
		cout << "Tester not found.\n\n";
}



// Purpose: Swap two tester variables
// Parameters: Tester &a: tester to be swapped with b
//             Tester &b: tester to be swapped with a
// Return: None (however the testers are passed by reference)
void Swap(Tester &a, Tester &b) {
	Tester temp = a;
	a = b;
	b = temp;
}



// Purpose: Preform a selection sort on an array of testers,
//          sorting by score ascending
// Parameters: Tester arr[]: array of testers to be sorted
//             const unsigned short int: portion of the array to sort
// Return:
void SelectionSort(Tester arr[], const unsigned short int size) {
	// loop until sorted
	for (int pass = 0; pass < size - 1; pass++) {
		int min_tester = pass;
		// loop through testers
		for (int tester = pass; tester < size; tester++) {
			// if comparison holds, get new min tester
			if (arr[tester].get_score() < arr[min_tester].get_score()) {
				min_tester = tester;
			}
		}
		// swap min_tester to correct place
		Swap(arr[min_tester], arr[pass]);
	}
}