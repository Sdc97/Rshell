#ifndef INPUTRE_TESTS
#define INPUTRE_TESTS

#include <fstream>
#include "gtest/gtest.h"
#include "../header/InputRe_op.hpp"
#include "../header/Cmnd.hpp"

TEST(InputRedirectionTestSet,inputCapital) {
	ofstream output;
	output.open("out.txt");

	output <<"Professor Brian Crites" <<endl;
	output.close();

	Cmnd* l =new Cmnd(4);
	Cmnd* r =new Cmnd(2);
	(*l)[0] =(char*)"tr";
	(*l)[1] =(char*)"a-z";
	(*l)[2] =(char*)"A-Z";
	(*l)[3] =NULL;
	(*r)[0] =(char*)"out.txt";
	(*r)[1] =NULL;

	Executable* input =new InputRe_op();
	input->set_left(l);
	input->set_right(r);

	EXPECT_EQ(input->run_command(),true);
}

TEST(InputRedirectionTestSet,cat) {
	Cmnd* l =new Cmnd(2);
	Cmnd* r =new Cmnd(2);
	(*l)[0] =(char*)"cat";
	(*l)[1] =NULL;
	(*r)[0] =(char*)"out.txt";
	(*r)[1] =NULL;

	Executable* input =new InputRe_op();
	input->set_left(l);
	input->set_right(r);

	EXPECT_EQ(input->run_command(),true);
}

TEST(InputRedirectionTestSet,rshell) {
	system("echo echo hello > out.txt; echo exit >> out.txt");

	Cmnd* l =new Cmnd(2);
	Cmnd* r =new Cmnd(2);
	(*l)[0] =(char*)"./rshell";
	(*l)[1] =NULL;
	(*r)[0] =(char*)"out.txt";
	(*r)[1] =NULL;

	Executable* input =new InputRe_op();
	input->set_left(l);
	input->set_right(r);

	EXPECT_EQ(input->run_command(),true);
}

#endif
