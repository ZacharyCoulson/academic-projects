/*
Class: tester

An object representing a tester, holds their score and name.
Default copy constructor is used. Includes a base and parametrized constructor. 
Uses a virtual deconstructor. Name and score can be set and received using the 
setter and getter functions. Includes a output function for the testers data.
*/


#ifndef TESTER_H
#define TESTER_H
#include <string>
#include <ostream>

class Tester
{
    protected:
        std::string _name {};
        unsigned short int _score {}; 

    public:
        Tester() : _score(0) {}
        Tester(std::string arg_name, unsigned short int arg_score) : _name(arg_name), _score(arg_score) {}
        virtual ~Tester();
        // setters
        bool set_name(const std::string& a_name);
        bool set_score(unsigned short int a_score);
        // getters
        std::string get_name() const;
        unsigned short int get_score() const;
        // output
        void output(std::ostream& os) const;


};

#endif // TESTER_H