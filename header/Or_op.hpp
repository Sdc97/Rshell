#ifndef OR_OP
#define OR_OP

#include "Connector.hpp"

class Or_op : public Connector {
public:
  Or_op(Executable* l, Executable* r);
  Or_op();
  string getType() { return "OR"; }
  bool run_command();
  void set_left(Executable*);
  void set_right(Executable*);
  Executable* get_left();
  Executable* get_right();
  string show();
};

#endif
