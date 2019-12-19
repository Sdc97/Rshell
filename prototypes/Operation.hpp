#ifndef __OPERATION__
#define __OPERATION__

#include "Executable.hpp"

class Operation : public Executable {
private:
  Executable* left;
  Executable* right;
public:
  Operation(Executable*,Executable*);
  bool run_command();
  Executable* get_left();
  Executable* get_right();
  void set_left(Executable*);
  void set_right(Executable*);
  void show();
};

#endif
