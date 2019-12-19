#ifndef OUTPUTRE_OP
#define OUTPUTRE_OP

#include <fcntl.h>
#include <sys/stat.h>
#include "Connector.hpp"
#include "Cmnd.hpp"

class OutputRe_op : public Connector {
	private:
	int append;
	public:
	OutputRe_op(int);
	string getType() {return "OUTPUTRE";}
//	char** visitCmnd(Cmnd*);
	bool run_command();
	void set_left(Executable*);
	void set_right(Executable*);
	Executable* get_left();
	Executable* get_right();
	string show();
};

#endif
