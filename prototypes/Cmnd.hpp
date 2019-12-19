#ifndef __COMMAND__
#define __COMMAND__

#include "Executable.hpp"

class Cmnd : public Executable {
private:
  const int SIZE = 3;
  char* command[SIZE];
public:
  Cmnd(char**);
  Cmnd();
  void set_left(Executable*);
  void set_right(Executable*);
  Executable* get_left();
  Executable* get_right();
  bool run_command();
  void show();
};

#endif
