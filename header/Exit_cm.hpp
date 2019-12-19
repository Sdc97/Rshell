#ifndef EXIT_CM
#define EXIT_CM

#include "Cmnd.hpp"

class Exit_cm : public Cmnd {
	public:
	Exit_cm(int s) :Cmnd(s) {
		(*this)[0] =(char*)"exit";
		(*this)[1] =NULL;
	}
	bool run_command() {
		exit(0);
	}
};

#endif
