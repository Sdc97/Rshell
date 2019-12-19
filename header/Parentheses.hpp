#ifndef PARENTHESES
#define PARENTHESES

#include "Executable.hpp"

class Parentheses :public Executable {
private:
  bool right;
public:
  Parentheses(char type) {
    if(type == '(') {
      right = true;
    } else {
      right = false;
    }
  }
  string getType() {
    if(right)
      return "(";
    else 
      return ")";
  }
  char** get_command() {}
  bool run_command() {
    cout << "This should never show, run_command in parentheses." << endl;
    return true;
  }
  void set_command(Executable* c) {
    cout << "This should never show. set_command in parentheses." << endl;
  }
  void set_left(Executable*l) {}
  void set_right(Executable*r) {}
  string show() {return "parentheses";}
};

#endif
