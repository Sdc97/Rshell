#ifndef EXECUTABLE
#define EXECUTABLE

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;

class Executable {
public:
  virtual string getType() = 0;
  virtual char** get_command() =0;
  virtual bool run_command() = 0;
  virtual void set_left(Executable*) =0;
  virtual void set_right(Executable*) =0;
  virtual string show() =0;
};

#endif
