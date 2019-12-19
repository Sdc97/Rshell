#ifndef OROP
#define OROP

#include "Executable.hpp"
#include "Operator.hpp"

class Or_op : public Operator {
public:
  Or_op(Executable*,Executable*);
  Executable* get_left();
  Executable* get_right();
  void set_left(Executable*);
  void set_right(Executable*);
  bool run_command();
  void show();
};

#endif
