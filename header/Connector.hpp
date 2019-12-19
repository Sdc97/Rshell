#ifndef CONNECTOR
#define CONNECTOR

#include "Executable.hpp"
#include "Cmnd.hpp"

class Connector : public Executable {
	protected:
	Executable* left;
	Executable* right;
	public:
	virtual bool run_command() =0;
	virtual char** get_command() {}
	virtual void set_left(Executable*) =0;
	virtual void set_right(Executable*) =0;
	virtual Executable* get_left() =0;
	virtual Executable* get_right() =0;
};

#endif

