#ifndef __Accessor__
#define __Accessor__

#include "Executable.hpp"

class Accessor : public Executable {
private:
  vector<Executable*> e;
public:
  Accessor(vector<Executable*>);
  Accessor();
  bool run_command();
  Executable* get_left();
  Executable* get_right();
  void set_left(Executable*);
  void set_right(Executable*);
};

#endif
