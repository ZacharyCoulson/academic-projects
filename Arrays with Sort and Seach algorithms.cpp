/******************************************************************************
scores_search_and_sort.cpp

Alex Coulson
CS161 Spring 2025, Mitch Priestley
All three parts, all points 

Purpose: Display common search and sort methods for programming.

Specification: The program outputs a welcome message and then reads a list of 
names and corresponding scores from a file into two parallel arrays. It displays
the unsorted arrays and performs a linear search to find a specific name, then 
outputs the score if found or a "not found" message otherwise.

Next, the arrays are sorted using selection sort, based on the scores. Both the
scores and names are swapped in parallel to maintain alignment. After sorting, 
the program displays the updated arrays and performs a binary search to find a 
specific score and outputs the corresponding name.

Then, the arrays are sorted alphabetically by name using bubble sort, and 
displayed again. Binary search is used to find a name, and its corresponding 
score is output. Then it identifies and displays the names of people with the 
highest and lowest scores by searching through the arrays using the values of 
the last and first elements, respectively, as references.

Finally, the program clears the arrays, zeros variables, displays a sign off 
message, and ends normally.

Sources: Starting out with C++ 9th edition
         Mitch Priestley
         Programiz

*******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

// Function prototypes
int BinarySearch(int, int[], int, int);
int BinarySearch(string, string[], int, int);
int LinearSearchArrays(string, string[], int[], int, int);
int ReadFileToArrays(string, string[], int[], int);
void BubbleSort(string[], int[], int);
void ClearArray(int[], int);
void ClearArray(string[], int);
void OuputArrays(string[], int[], int);
void OutputScorers(string[], int[], int, string = "highest");
void OutputSearch(string, int, int[], int);
void OutputSearch(int, int, string[], int);
void SelectionSort(string[], int[], int);
void Swap(int&, int&);
void Swap(string&, string&);

int main()
{
    // Declare constants  
	const string file_name = "scores.txt"; // File that holds names and scores
	const int MAX = 100, // Max size of the arrays
	      NOT_FOUND = -1; // sentinel marking if any search does not find target
	/* Examples of targets to search for, in a normal program would be user 
	input. Feel free to change thise two values to anything that fits the type*/
    const string s_target = "Felicia"; // Example target for searching
    const int t_score = 20;  // Example target for searching
    // Declare variables 	      
	string names[MAX]; // Array of names that are parallel to scores
	int scores[MAX] {0}; // Array of scores that is parallel to names
	int arrays_sizes = 0, // Written size of the arrays
	    t_val = 0; // Holds the score corresponding to a targeted name

	// Welcome user to the program
	cout << "Welcome to the scores search and sort program.\n\n\n";
	// Import file of scores & names into the arrays
	arrays_sizes = ReadFileToArrays(file_name, names, scores, MAX);
	// Output scores
	cout << "Unsorted array.\n";
	OuputArrays(names, scores, arrays_sizes);
	// Input the score of the target using a linear search
	cout << "Now doing a linear search of " << s_target << "...\n";
	t_val = LinearSearchArrays(s_target, names, scores, arrays_sizes,NOT_FOUND);
	// Output the score of the target
	OutputSearch(s_target, t_val, scores, NOT_FOUND);
	// Sort the arrays based on the scores using selection sort
	SelectionSort(names, scores, arrays_sizes);
	cout << "Binary sorted array based on scores.\n";
	// Output Scores
	OuputArrays(names, scores, arrays_sizes);
	// Input the score of the target using a binary search
	cout << "Now doing a binary search of " << t_score << "...\n";
	t_val  = BinarySearch(t_score, scores, arrays_sizes, NOT_FOUND);
	// Output the name of the target
	OutputSearch(t_score, t_val, names, NOT_FOUND);
	// Sort alphabetically using bubble sort
	cout << "Bubble sorted array based on names.\n";
	BubbleSort(names, scores, arrays_sizes);
	// Output Arrays alphabetically
	OuputArrays(names, scores, arrays_sizes);
	t_val = 0;
	// Look up name using binary search
	cout << "Now doing a binary search of " << s_target << "...\n";
	t_val = BinarySearch(s_target, names, arrays_sizes, NOT_FOUND);
	// Output the score of the target
	OutputSearch(s_target, t_val, scores, NOT_FOUND);
	// Output the names with the highest score
	cout << "Now outputing the people with the highest score...\n";
	OutputScorers(names, scores, arrays_sizes, "highest");
	// Output the names with the lowest score
	cout << "Now outputing the people with the lowest score...\n";
	OutputScorers(names, scores, arrays_sizes, "lowest");
// Wrap Up
	// Clear variables
	ClearArray(names, MAX);
	ClearArray(scores, MAX);
	arrays_sizes = t_val = 0;
	// Sign off
	cout << "\nProgram Complete.";
	// End normally
	return 0;
}

// Purpose: Find the label of a target
/* Arguments: Int of the target to search for, int array of values,
int size of the parallel arrays, int sentinel that marks if the value was
not found*/
// Return: Location of label
int BinarySearch(int target, int int_arr[], int size, int sentinel) {
	int minimum = 0, // Start of search
	    maximum = size - 1, // Max location of search
	    result = sentinel; // Start location as not found
	// While searching
	while (minimum <= maximum) {
		// Update middle
		int middle = minimum + (maximum - minimum) / 2;
		// location is found
		if (int_arr[middle] == target)
			return middle;
		// Remove left half is location is not in there
		else if (int_arr[middle] < target)
			minimum = middle + 1;
		// Remove right half is location is not in there
		else
			maximum = middle - 1;
	}
	// Return location if found, or sentinel if not found
	return result;
}

// Purpose: Find the value of a target
/* Arguments: String of targets label, string of labels to search, int of size
of search, int of sential marking if not found*/
// Return: location of value
int BinarySearch(string target, string str_arr[], int size, int sentinel) {
	int minimum = 0, // Start of search
	    maximum = size - 1, // Max location of search
	    result = sentinel; // Start location as not found

	// While searching
	while (minimum <= maximum) {
		// Update middle
		int middle = minimum + (maximum - minimum) / 2;
		// location is found
		if (str_arr[middle] == target)
			return middle;
		// Remove left half is location is not in there
		else if (str_arr[middle] < target)
			minimum = middle + 1;
		// Remove right half is location is not in there
		else
			maximum = middle - 1;
	}
	// Return location if found, or sentinel if not found
	return result;
}
// Purpose: Find the value of a target
/* Arguments: string of the target label to be tested, string array of labels,
int array of values, int size of the parallel arrays, int sentinel that marks
if the label was not found*/
// Return: location of value
int LinearSearchArrays(string target, string str_arr[], int int_arr[],
                       int size, int sentinel) {
	int result = sentinel; // Start location as not found
	bool searching = true; // Determins if array is being searching
	// While searching array and inside array
	for (int idx = 0; idx < size && searching; ++idx) {
		// If target is found
		if (target == str_arr[idx]) {
			// Return location
			result = idx;
			// Stop searching
			searching = false;
		}
	}
	// Return location if found, or sentinel if not found
	return result;
}


/*Purpose: Read a pre-formated file of strings and ints and import into two
arrays parallelly*/
/* Arguments: String name of the file to be read from, string array of labels
to be written into, int array of values to written into.*/
// Return: Written size of the parallel arrays
int ReadFileToArrays(string file, string str_arr[], int int_arr[], int size) {
	bool reading_file = true;
	int data_count = 0;
	// Open file
	ifstream ifile(file);
	// If file does not exist
	if (!ifile) {
		cout << "Error! " << file << " was not found!\n";
		exit(1);
	}
	// Get labels and values by looping through parallel arrays
	for (data_count = 0;  data_count < size && reading_file; ++data_count) {
		// Read labels
		ifile >> str_arr[data_count];
		// Read values
		ifile >> int_arr[data_count];
		// Check if file is over
		if (ifile.eof())
			reading_file = false;
	}
	// Close file
	ifile.close();
	// Written size of parallel arrays
	return data_count;
}


// Purpose: Sort parallel arrays using bubble sort
// Arguments: string array to be sort, int array to be sort, size of arrays
// Return: None
void BubbleSort(string str_arr[], int int_arr[], int size) {
	// While arrays are unsorted
	for (int pass = 0; pass < size - 1; ++pass) {
		// Check each array
		for (int idx = 0; idx < size - pass - 1; ++idx) {
			// If unsorted
			if (str_arr[idx] > str_arr[idx + 1]) {
				// Bubble strings
				string temp_str = str_arr[idx];
				str_arr[idx] = str_arr[idx + 1];
				str_arr[idx + 1] = temp_str;
				// Bubble ints
				int temp_int = int_arr[idx];
				int_arr[idx] = int_arr[idx + 1];
				int_arr[idx + 1] = temp_int;
			}
		}
	}
}


// Purpose: Zeroize a int array
// Arguments: Int array to be cleared, size of the int array
// Return: None
void ClearArray(int arr[], int size) {
	for (int idx = 0; idx < size; ++idx)
		arr[idx] = 0;
}


// Purpose: Clear a string array
// Arguments: String array to be cleared, size of the string array
// Return: None
void ClearArray(string arr[], int size) {
	for (int idx = 0; idx < size; ++idx) {
		// Create null charaters
		arr[idx] = string(arr[idx].length(),'\0');
		arr[idx].clear();
	}
}


// Purpose: Simultaneously output a two parallel arrays of strings and ints
/* Arguments: String array of lables to be output, parallel array of numbers
to be output */
// Return: None
void OuputArrays(string str_arr[], int int_arr[], int size) {
	// While iside of arrays
	for (int idx = 0; idx < size; ++idx) {
		// Output arrays
		cout << setw(10) << left << str_arr[idx]  << setw(5) << right
		     << int_arr[idx] << endl;
	}
	cout << endl; // Formating
}

// Purpose: Output the labels of the highest or lowest values
/* Arguments: String array of labels, int array of valules, size of arrays,
string of which location of values is to be output*/
void OutputScorers(string str_arr[], int int_arr[], int size, string location) {
	int element = 0, // Location of output
	    value = int_arr[0]; // Value of location
	// If the location is highest values
	if (location == "highest") {
		// Find highest value
		for (int idx = 0; idx < size; ++idx) {
			if (int_arr[idx] > value)
				value = int_arr[idx];
		}
	}
	else {
		// If the location is lowest values
		for (int idx = 0; idx < size; ++idx) {
			// Find lowest value
			if (int_arr[idx] < value)
				value = int_arr[idx];
		}
	}
	// Output labels with matching values
	for (int idx = 0; idx < size; ++idx) {
		if (int_arr[idx] == value)
			cout << str_arr[idx] << ", ";
	}
	cout << endl << endl; // formating
}


// Purpose: Output findings from a search.
/* Arguments: String of target, int of target's value, int of sentinel marking
if the target was not found */
// Return: None
void OutputSearch(string target, int value, int arr[], int sentinel) {
	// Was not found
	if (value == sentinel)
		cout << target << " was not found.\n";
	// Labels value was found
	else
		cout << target << "'s score is: " << arr[value] << ".\n\n";
}


// Purpose: Output findings from a search.
/* Arguments: Int of target, string of target's label, int of sentinel marking
if the target was not found */
// Return: None
void OutputSearch(int target, int value, string arr[], int sentinel) {
	// Was not found
	if (value == sentinel)
		cout << target << " was not found.\n";
	// Values **first** label was found
	else
		cout << arr[value] << " has a score of " << target << ".\n\n";
}


// Purpose: Swap two ints by refrence
// Arguments: First int to be swapped, second int to be swapped
// Return: None
void Swap(int &val_1, int &val_2) {
	int temp = val_1;
	val_1 = val_2;
	val_2 = temp;
}


// Purpose: Swap two strings by refrence
// Arguments: First string to be swapped, second string to be swapped
// Return: None
void Swap(string &val_1, string &val_2) {
	string temp = val_1;
	val_1 = val_2;
	val_2 = temp;
}


// Purpose: Sort two parallel arrays using the selection sort
/* Arguments: String array to be sorted, parallel int array to be sorted, size
of the arrays as an int*/
// Return: None
void SelectionSort(string str_arr[], int int_arr[], int size) {
	// Loop through arrays for first value
	for (int pass = 0; pass < size-1; ++pass) {
		int minimum = pass; // Start of search and smallest value
		// Loop through arrays for second value
		for (int idx = pass+1; idx < size; ++idx) {
			// Find which value is larger
			if(int_arr[idx] < int_arr[minimum])
				minimum = idx; // Update start of search if a smaller val found
		}
		// Sort values, move smallest value to start of search
		Swap(int_arr[minimum], int_arr[pass]);
		Swap(str_arr[minimum], str_arr[pass]);
	}
}


