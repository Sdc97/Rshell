#ifndef __CMND_MOCK__
#define __CMND_MOCK__

#include "../header/Executable.hpp"

using namespace std;

class Cmnd_mock : public Executable {
private:
  bool pass;
public:
  Cmnd_mock(bool status) {
    pass = status;
  }
  bool run_command() {
    return pass;
  }
  char** get_command() {}
  string getType() { return "INVALID"; }
  void set_left(Executable* l) {}
  void set_right(Executable* r) {}
  string show() { }
  char* &operator[](int) {};
};

#endif
