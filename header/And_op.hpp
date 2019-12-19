#ifndef AND_OP
#define AND_OP

#include <iostream>

using namespace std;

#include "Connector.hpp"

class And_op : public Connector {
	public:
	And_op(Executable* l, Executable* r);
	And_op();
  string getType() { return "AND"; }
	bool run_command();
	void set_left(Executable*);
	void set_right(Executable*);
	Executable* get_left();
	Executable* get_right();
	string show();
};

#endif
