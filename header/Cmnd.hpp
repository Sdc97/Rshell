#ifndef CMND
#define CMND

#include <iostream>
#include "../header/Executable.hpp"

using namespace std;

class Cmnd : public Executable {
	protected:
	char** command;
	const int SIZE;
	public:
  virtual string getType() { return "CMND"; }
	Cmnd(int size);
	~Cmnd();
	char* &operator [](int i);
	bool run_command();
	const int get_size();
	void set_left(Executable*);
	void set_right(Executable*);
	string show();
	char** get_command() {return this->command;}
};

#endif
