#ifndef __PARSER__
#define __PARSER__

#include "Executable.hpp"


//Have not decided on a single parser yet,
// Both src_token and src_iterative have 
// woking parsers.
class Parser {
private:
  string input;
  vector<Executable*> commands;
public:
  Parser(string in);
  vector<Executable*> Parse();
};

#endif
