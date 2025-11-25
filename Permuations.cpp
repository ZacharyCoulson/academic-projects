/******************************************************************************
week_5_program_ec.cpp

Week 5 Program
Alex XXXXXXX
CS 250 Fall XXXXX XXXXXXXXX
            

Purpose: Output and count permutations from diffrent sets.
Specification: Specification: Welcome user to program. Prompt user for the 
length of the permutations, and validate input. Prompt user to choose which part
of the alphanumeric set to use, and validate input. Output estimated 
permutations of the chosen set. Loop though recursive functions to output 
permutations. After outputting backspace to reset the position. Increment 
permutation counter. Once permutations finish output counted permutations. 
Leave a sign off message, and then end normally.

Sources:
Kielx             https://gist.github.com/Kielx/2917687bc30f567d45e15a4577772b02
For colors

Google gemini search result, of how to keep variable values in recursive 
functions. (Taught me to use static variables)
*******************************************************************************/
#include <cctype>  // For toupper
#include <cmath>   // For power
#include <iomanip> // For setprecision
#include <iostream>
#include <string>

// Text colors
#define RESET   "\033[0m"
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */

using namespace std;

const string alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn"
                            "opqrstuvwxyz"; /* String containting all
                            alphanumeric chars used in permutations function
                            Index 0-9 = 0 - 9
                            Index 10-35 = A-Z
                            Index 10-61 = A-Z, a-z
                            Index 0-61 = all alphanumeric characters */

// function prototypes
char prompt_choice();
int get_length();
int output_char(int, int, int);
void permutations(char, int);




int main()
{
	// Welcome user
	cout << "Welcome to the permutations program!\n\n\n";
	// Prompt user with choice
	permutations(prompt_choice(), get_length());
	// Sign off
	cout << "\n\nProgram complete, goodbye!";
	// End normally
	return 0;
}



// Purpose: Prompt user for a int value 1-7, validate, and return
// Arguments: None
// Return: Valid response from user
int get_length() {
    int response = 0;  // Input from the user for the permutations size
    // Ask for input
    cout << "Please choose the length of your string (suggested: 1-7): ";
    // If Invalid input
    while (!(cin >> response) || response < 1) {
        // Ask again
        cout << BOLDRED << "Invalid input. " << RESET 
             << "Please enter an integer ≥ 1: ";
        // Reset cin
        cin.clear();
        cin.ignore(1024, '\n');
    }
    // Reset cin
    cin.clear();
    cin.ignore(1024, '\n');
    // Warn user if large input
    if (response > 7) {
        cout << BOLDYELLOW << "Warning! length's > 7 may take awhile!" 
        << RESET << endl;
    }
    // Return the size of the permutations
    return response;
}



// Purpose: Prompt user for a char value {A, B, C, D}, validate, and return
// Arguments: None
// Return: Valid response from user
char prompt_choice() {
	string valid_responses = "AaBbCcDd";  // All acceptable inputs
	char response = '\0';                 // input from user
	bool val_resp = false;                // validity of the input from the user
	int size = sizeof(valid_responses);   // Size of the set of valid responses
    
	// Output Choices to user
	cout << "Choose one of the following character sets:\n"
	     << "  A) 0 - 9\n"
	     << "  B) A - Z\n"
	     << "  C) A - Z, a - z\n"
	     << "  D) all alphanumeric characters\n";
	// Prompt and validate responses
	while (!val_resp) {
		cout << "Your choice? ";
		cin.get(response);
		// Check for valid responses
		for (int canidate = 0; canidate <= size && !val_resp; ++canidate) {
			// If valid response
			if (response == valid_responses[canidate])
				val_resp = true;
		}
		// If response Invalid
		if (!val_resp) {
			cin.ignore(1024, '\n');
			cout << BOLDRED "Invalid input!" << RESET 
			     << " Please enter A, B, C, or D.\n";
		}
	}
	// Return valid response as a uppercase letter
	return toupper(response);
}




// Purpose: Output permutations of sets
// Arguments: Choice of which charater set (part of alphanumeric) to use
// Return: None
void permutations(char choice, int permutations_length) {
	int start = 0,                  // Starting index of the alphanumeric set
	    end = 0,                    // Ending index of the alphanumeric set
	    size = 0,                   // Number of characters in set used
	    true_permutations = 0,      // Counter variable for permutations output
	    estimated_permutations = 0; // Calucated variable for permutations
	    
	// Get which input
	switch (choice) {
	case 'A':      // 0 - 9
		start = 0;
		end = 9;
		break;
	case 'B':      // A-Z
		start = 10;
		end = 35;
		break;
	case 'C':     // A-Z, a-z
		start = 10;
		end = 61;
		break;
	case 'D':     // all alphanumeric characters
		start = 0;
		end = 61;
		break;
	default:      // Error!
		cout << "ERROR! the prompt_choice has failed to validate the input.\n";
		return;
	}
	// Calulat set size
	size = end-start+1;
	// Output estimated permutations
	cout << "\n\nWe anticipate showing you " << setprecision(8) 
	     << pow(size,permutations_length) << " permutations of "  
	     << permutations_length << " characters \nat a time, each chosen from "
	     << "the following set of " << size << " characters: \n";
	for (int position = start; position <= end; ++position) {
		cout << alphanumeric[position];
	}
	cout << endl << endl; // Formating
	// Create nested loops for each character place
    true_permutations = output_char(start, end, permutations_length);
	cout << endl << endl; // Formating
	// Output the count permutations that were outputed
	cout << true_permutations << " permutations outputted.\n";
}



// Purpose: Output permutations
// Arguments: Int of start of set, int of end of set, int of permutations length
// Return: int of number of permutations output
int output_char(int start, int end, int recursions) {
	static bool initialized = false; // Truth value of initialzation has happend
	static int length = 0;           // Total length of permutation
	static string permutation;       // String of permutation
	int true_permutations = 0;       // Counter variable for permutations outpu
	// Setup on first run
	if (!initialized) {
		// Get length
		length = recursions;
		// Create buffer permutation
		permutation = string(length, ' ');
		// finish initialzation
		initialized = true;
	}
	// Output permutation
	if (recursions == 0) {
		cout << permutation;
		// Backspace to reset position
		for (int backspace = 0; backspace < length; ++backspace) {
			cout << '\b';
		}
		cout.flush();
		return 1; // count permutation
	}
	// Current character position to modify
	int position = length - recursions;
	// Loop through all characters in the alphanumeric set
	for (int idx = start; idx <= end; ++idx) {
		permutation[position] = alphanumeric[idx];
		true_permutations += output_char(start, end, recursions - 1);
	}
	// Return the amount of permutations output
	return true_permutations;
}


