/*******************************************************************************
wk10_binary_files.cpp

Alex Coulson 
CS161 Spring 2025, Mitch Priestley

Purpose: Experiment with different types of sort and searches with struct arrays 
and RAF
specification: Output a greeting message. Ensure a file exists by attempting to
open it. If it doesn’t exist, create one with base values. Read the contents of
the file into an array. Output the data inside the array. Throughout all 
searches and outputs, if the target is not found, no data will be output and the
search will return “-1.” Perform a linear search for a specific name inside the 
array and output the findings. Find the location of the result from the linear 
search in the file. Perform a selection sort on the array alphabetically. Output
the array’s contents. Perform a binary search for a specific student’s name. 
Output that student’s sequence number. Ensure the array and file match, then 
search the file for that sequence and output the corresponding student’s data.
Wrap up by clearing all variables, clearing the array of students, outputting a
sign-off message, and returning 0.

Sources: Starting out with c++ 9th ed (ch 12, ch 6)
       Mitch Priestley labs 
*******************************************************************************/
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const string FILENAME = "scores.dat"; // File to store Students
const int MAX = 100; // Max amount of Students

// Struct for stund names and scores (and seq # for position on the disk)
struct Student {
	int seq = 0; // Remembers where this student is stored from the file
	char name[10] {}; // Remembers where this students name from the file
	int score = 0; // Remembers Student's score (as a percentage) from the file

	// Display all of student info
	void display() {
		cout << left << setw(4) << seq  // Student's number
		     << setw(11) << name        // Student's name
		     << right << setw(4) << score << "%" << endl; // Student's score %
	}
};

// Function portotypes
int binary_Search(Student[], int, string);
int linear_Search(Student[], int, string);
int write_To_Array(Student[]);

void clear_Array(Student[], int);
void display_Data(Student[], int);
void ensure_File();
void find_In_File(int);
void output_Search(string, int);
void selection_Sort(Student[], int);
void Swap(Student&, Student&);
void write_To_File(Student[], int);

int main() {
	// Declare variables
	const string target_name = "Alex"; // Example input, change to whatever
	Student students[MAX]; // Array of students, populated from file
	int rec_count = 0, // Amount of students, counted from file
	    target_seq = 0; // Holds the targets seq #, found from searches
// Part 1
	cout << "Welcome to the binary file program.\n";
	// Create & populate file if does not exist
	ensure_File();
	// Populate the students array from the file, & tack amount off arr written
	rec_count = write_To_Array(students);
	// Display the contents of the students in the students array
	cout << "\nNow outputing base data in array.\n";
	display_Data(students, rec_count);
	// Find the seq # of a specific students name
	target_seq = linear_Search(students, rec_count, target_name);
	cout << "\nNow displaying a linear search search for " <<target_name<<".\n";
	output_Search(target_name, target_seq);
	// Display specifc students data
	if (target_seq !=  -1) {
	cout << "\nNow outputting " << target_name << "'s data.\n";
	find_In_File(target_seq); }
	// Sort array using selction sort based off names
	selection_Sort(students, rec_count);
	// Display data in student array
	cout << "\nNow outputing all data based on a selction sort.\n";
	display_Data(students, rec_count);
	// Locate a students seq using a binary search
	target_seq = binary_Search(students, rec_count, target_name);
	// Output the targets data based on the binary search
	cout << "\nNow displaying a binary search search for "<<target_name<< ".\n";
	output_Search(target_name, target_seq);
	// Match file with array
	write_To_File(students, rec_count);
	if (target_seq !=  -1) {
	// Search file for target and output
	cout << "\nNow outputting " << target_name << "'s data.\n";
	find_In_File(target_seq); }
// wrap up
	// Clear variables
	clear_Array(students, rec_count);
	rec_count = target_seq = 0;
	// Sign off
	cout << "\nProgram complete.";
	// End Normally
	return 0;
}

// Purpose: Preform a binary search on a array with a type of Student 
// Arguments: Student Array to search, int of section of array to search, 
//            string of the target go search for 
// Return: Seq of student found, or -1 if not found 
int binary_Search(Student std_arr[], int size, string target) {
	int minimum = 0, // Starting portion to read from 
	maximum = size - 1; // Ending position to stop reading 
	 // While inside current range 
	while (minimum <= maximum) {
	    // Find the middle position of array
		int middle = minimum + (maximum - minimum) / 2;
		// If match return students seq #
		if (std_arr[middle].name == target)
			return middle;
		// If less remove left half	
		else if (std_arr[middle].name < target)
			minimum = middle + 1;
		// If more remove right half	
		else
			maximum = middle - 1;
	}
	// If never found return -1 
	return -1;
}


// Purpose: Preform a linear search on a array with a type of Student 
// Arguments: Student Array to search, int of section of array to search, 
//            string of the target go search for 
// Return: Seq of student found, or -1 if not found 
int linear_Search(Student std_arr[], int size, string target) {
    // While inside populated part of array
	for (int idx = 0; idx < size; ++idx)
	    // Compare idx.name to the target name 
		if (std_arr[idx].name == target)
		    // If name is found return seq #
			return std_arr[idx].seq;
	// If name was never found, return -1 		
	return -1;
}


// Purpose: Write into an array with the type of Student from a file 
// Arguments: Array with the type of Student to be written to
// Return: Written size of array 
int write_To_Array(Student std_arr[]) {
    // Open binary file for reading  
	fstream file(FILENAME, ios::in | ios::binary);
	// Find number of students
	file.seekg(0, ios::end);
	int result = file.tellg() / sizeof(Student);
	// Write file into array while within the array
	file.seekg(0, ios::beg);
	file.read(reinterpret_cast<char*>(std_arr), result * sizeof(Student));
	// Close file 
	file.close();
	// Return populated portion of array 
	return result;
}


// Purpose: Clear an array with the type of Student
// Arguments: Array with type of Student to be cleared, portion of array cleared
// Return: None
void clear_Array(Student arr[], int size) {
    // While inside portion of array 
	for (int idx = 0; idx < size; ++idx) {
		arr[idx].seq = 0; // Clear student's seq #
		arr[idx].score = 0; // Clear student's sore
		// Loop through name
		for (int letter = 0; letter < sizeof(arr[idx].name); ++letter) {
			arr[idx].name[letter] = '\0'; // Clear one letter
		}
	}
}


// Purpose: Display data in a array with type Student, with a header 
// Arguments: Array with type Student to be displayed, portion of array output
// Return: None
void display_Data(Student std_arr[], int size) {
    // Display header
	cout << left << setw(4) << "#" << setw(11) << "NAME"
	     << right << setw(4) << "SCORE" << endl;
	// Display array
	for (int idx = 0; idx < size; ++idx)
		std_arr[idx].display();
}


// Purpose: Make sure the file exists, if not create and populate it
// Arguments: None 
// Return: None
void ensure_File() {
    // Check if file exists by attempting to open
	fstream file(FILENAME, ios::in | ios::binary);
	// If file does not exist 
	if (!file) {
	    // Open a binary file for writing
		file.open(FILENAME, ios::out | ios::binary);
		// Create a temporary array of Students
		Student students[] = {
			{0, "Bart", 65},
			{1, "Trish", 66},
			{2, "Craig", 97},
			{3, "Eduardo", 99},
			{4, "Alex", 70},
			{5, "Albert", 68},
			{6, "Oliva", 92},
			{7, "Johnathan", 60},
			{8, "William",  100}
		};
		// Find number of students
		int count = sizeof(students) / sizeof(students[0]);
		// Write temporary array into file while within the array
		file.write(reinterpret_cast<char*>(students), count * sizeof(Student));
	}
	// Close file 
	file.close();
}



// Purpose: Find a specifc Student in a file of multiple Student 
// Arguments: specifc Student seq # to be searched for 
// Return: None
void find_In_File(int seq) {
    // Open binary file for reading
	fstream file(FILENAME, ios::in | ios::binary);
	// Seek location of student
	file.seekg(seq * sizeof(Student));
	Student found;
	// Read contents of student
	file.read(reinterpret_cast<char*>(&found), sizeof(Student));
	// Close file
	file.close();
	// Output findings
	found.display();
}


// Purpose: Output results of a search for a string 
// Arguments: String of the target that was searched, int of seq # or sentinel 
// Return: None
void output_Search(string name, int seq) {
    // If not found 
	if (seq == -1)
		cout << name << " was not found!\n";
	// If found
	else
		cout << name << " found at seq #" << seq << ".\n";
}


// Purpose: Perform a selction sort on an array with type of Student
// Arguments: Array with type Student to be searched,int of portion of array to
//            search.
// Return: None
void selection_Sort(Student std_arr[], int size) {
	for (int pass = 0; pass < size - 1; ++pass) {
		int minimum = pass;
		// Find the smallest name
		for (int idx = pass + 1; idx < size; ++idx) {
			if (strcmp(std_arr[idx].name, std_arr[minimum].name) < 0)
			// Update starting position if a smaller name is found
				minimum = idx;
		}
		if (minimum != pass)
		// If smallest name is unsorted swap 
			Swap(std_arr[minimum], std_arr[pass]);
	}
	// Reverse the sorting of the seq #
	for (int idx = 0; idx < size; ++idx)
		std_arr[idx].seq = idx;
}


// Purpose: Swap two Student values 
// Arguments: First Student to be swapped, Second Student to be swapped
// Return: None
void Swap(Student &val_1, Student &val_2) {
	Student temp = val_1;
	val_1 = val_2;
	val_2 = temp;
}


// Purpose: Write an array with type Student to a file 
// Arguments: Array with type Student to be written to file, portion of the 
//            array to write. 
// Return: None
void write_To_File(Student std_arr[], int rec_count) {
    // Open binary file for writing
	fstream file(FILENAME, ios::out | ios::binary);
	// Overwrite current file with contents of array
	file.write(reinterpret_cast<char*>(std_arr), rec_count * sizeof(Student));
	// Close file
	file.close();
}
