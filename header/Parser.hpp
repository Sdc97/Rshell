#ifndef PARSER
#define PARSER

#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <deque>

using namespace std;

#include "Exit_cm.hpp"
#include "Test_cm.hpp"
#include "And_op.hpp"
#include "Or_op.hpp"
#include "Parentheses.hpp"
#include "InputRe_op.hpp"
#include "OutputRe_op.hpp"
#include "Pipe_op.hpp"

class Parser {
	private:
	vector<Executable*> exe;	//Holds all commands
	bool quote =false;		//To know if there are any quote in the command while parsing
	string connectors ="&|()<>;";	//The connectors and end of command.
	void precheck(string&);		//Function that checks the command length and return if <1. Also deletes space between connectors and commands
	void preCreate(string);
	Executable* create(string);	//Creates the commands
	int count(string);		//Counts the number of commands in string
	void run();			//Run all commands in vector<Executable*> exe
  bool priority(Executable*,Executable*);
	Executable* process(vector<Executable*> con);
	public:
	string showCmnd(int);		//For testing purposes. Returns the the string of the command
	Parser(string);
	~Parser();
};
#endif
