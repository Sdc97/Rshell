#ifndef __PIPE_OP__
#define __PIPE_OP__

#include <unistd.h>
#include <sys/wait.h>
#include "Executable.hpp"
#include "Connector.hpp"
#include "Cmnd.hpp"

class Pipe_op : public Connector {
public:
  Pipe_op();
  string getType() { return "PIPE"; }
  bool run_command();
  void set_left(Executable*);
  void set_right(Executable*);
  Executable* get_left();
  Executable* get_right();
  string show();
};

#endif
