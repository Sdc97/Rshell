#ifndef EXECUTABLE
#define EXECUTABLE

class Executable {
public: 
  virtual void set_left(Executable*) = 0;
  virtual void set_right(Executable*) = 0;
  virtual Executable* get_left() = 0;
  virtual Executable* get_right() = 0;
  virtual bool run_command() = 0;
  virtual void show() = 0;
};

#endif
