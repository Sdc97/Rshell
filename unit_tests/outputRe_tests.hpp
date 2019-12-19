#ifndef OUTPUTRE_TESTS
#define OUTPUTRE_TESTS

#include "gtest/gtest.h"
#include "../header/Cmnd.hpp"
#include "../header/OutputRe_op.hpp"

TEST(OutputRedirectionTestSet,ls) {
	Cmnd* l =new Cmnd(2);
	Cmnd* r =new Cmnd(2);
	(*l)[0] =(char*)"ls";
	(*l)[1] =NULL;
	(*r)[0] =(char*)"h.txt";
	(*r)[1] =NULL;

	Executable* outputOver =new OutputRe_op(0);	//output overwrite
	outputOver->set_left(l);
	outputOver->set_right(r);

	Executable* output =new OutputRe_op(1);
	output->set_left(l);
	output->set_right(r);

	EXPECT_EQ(outputOver->run_command(),true);
	EXPECT_EQ(output->run_command(),true);
}

TEST(OutputRedirectionTestSet,appendCapital) {
	Cmnd* r =new Cmnd(2);
	(*r)[0] =(char*)"h.txt";
	(*r)[1] =NULL;

	Executable* capital =new OutputRe_op(0);
	capital->set_left(new Cmnd(0));
	capital->set_right(r);

	Executable* append =new OutputRe_op(1);
	append->set_left(new Cmnd(0));
	append->set_right(r);

	EXPECT_EQ(capital->run_command(),true);
	EXPECT_EQ(append->run_command(),true);
}

TEST(OutputRedirectionTestSet,echo) {
	Cmnd* l =new Cmnd(3);
	Cmnd* r =new Cmnd(2);
	(*l)[0] =(char*)"echo";
	(*l)[1] =(char*)"hello";
	(*l)[2] =NULL;
	(*r)[0] =(char*)"h.txt";
	(*r)[1] =NULL;

	Executable* over =new OutputRe_op(0);
	over->set_left(l);
	over->set_right(r);

	Executable* append =new OutputRe_op(1);
	append->set_left(l);
	append->set_right(r);

	EXPECT_EQ(over->run_command(),true);
	EXPECT_EQ(append->run_command(),true);
}

TEST(OutputRedirectionTestSet,quotes) {
	Cmnd* l =new Cmnd(2);
	Cmnd* r =new Cmnd(2);
	(*l)[0] =(char*)">>";
	(*l)[1] =NULL;
	(*r)[0] =(char*)"h.txt";
	(*r)[1] =NULL;

	Executable* over =new OutputRe_op(0);
	over->set_left(l);
	over->set_right(r);

	Executable* append =new OutputRe_op(1);
	append->set_left(l);
	append->set_right(r);

	EXPECT_EQ(over->run_command(),true);
	EXPECT_EQ(append->run_command(),true);
}
#endif
