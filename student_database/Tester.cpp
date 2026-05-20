#include "Tester.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Deconstructor 
Tester::~Tester() {
    _name = string(_name.length(), 0);
    _score = 0;
}

// Setters
bool Tester::set_name(const string& a_name) {
    bool result = false;
    if (a_name.length() >= 3 && a_name.length() <= 7) {
         _name = a_name;
         result = true;
    }
    return result;
}

bool Tester::set_score(unsigned short int a_score) {
    bool result = false;
    if (a_score <= 100) {
         _score = a_score;
        result = true;
    }
   return result;
}
 
// Getters
string Tester::get_name() const {
    return _name;
}

unsigned short int Tester::get_score() const {
    return _score;
}

void Tester::output(ostream& os) const {
    os << left << setw(10) << _name << right << setw(6) << _score << endl;
}