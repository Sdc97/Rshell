#ifndef INPUTRE_OP
#define INPUTRE_OP

#include <fcntl.h>
#include <sys/stat.h>
#include "Connector.hpp"

class InputRe_op : public Connector {
	public:
	InputRe_op();
	string getType() {return "INPUTRE";}
	bool run_command();
	void set_left(Executable*);
	void set_right(Executable*);
	Executable* get_left();
	Executable* get_right();
	string show();
};

#endif
