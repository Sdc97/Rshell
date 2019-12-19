#ifndef __CMND_TESTS__
#define __CMND_TESTS__

#include "gtest/gtest.h"
#include "../header/Cmnd.hpp"
#include "../mocks/cmnd_mock.hpp"

/* 
   Mock Tests
   Should return the following values:
   TRUE
   FALSE
*/
TEST(CmndTestSet, MockTest1) {
  Executable* mock1 = new Cmnd_mock(true);

  EXPECT_EQ(mock1->run_command(), true);
}

TEST(CmndTestSet, MockTest2) {
  Executable* mock1 = new Cmnd_mock(false);

  EXPECT_EQ(mock1->run_command(), false);
}

/*
  Test: SingleExecutable
  Actual: ls
  Expected Result:
  Listing of current directory
  Expected value: TRUE
*/
TEST(CmndTestSet, SingleExecutable) {
  Cmnd* mock1 = new Cmnd(2);
  (*mock1)[0] = (char*)"ls"; 
  (*mock1)[1] = NULL;
  cout << "$ " << mock1->show() << endl;
  EXPECT_EQ(mock1->show(), "ls");
  EXPECT_EQ(mock1->run_command(), true);
}

/*
  Test: OneArgument
  Actual: ls -a
  Expected Result:
  Listing of current directory, including hidden files.
  Expected value: TRUE
*/
TEST(CmndTestSet, OneArgument) {
  Cmnd* mock1 = new Cmnd(3);
  (*mock1)[0] = (char*)"ls"; 
  (*mock1)[1] = (char*)"-a";
  (*mock1)[2] = NULL;
  cout << "$ " << mock1->show() << endl;
  EXPECT_EQ(mock1->show(), "ls -a");
  EXPECT_EQ(mock1->run_command(), true);
}

/*
  Test: TwoArguments
  Actual: ls -a -l
  Expected Result:
  Listing of current directory with specifics, including
  hidden files.
  Expected value: TRUE
*/
TEST(CmndTestSet, TwoArguments) {
  Cmnd* mock1 = new Cmnd(4);
  (*mock1)[0] = (char*)"ls"; 
  (*mock1)[1] = (char*)"-a"; 
  (*mock1)[2] = (char*)"-l"; 
  (*mock1)[3] = NULL;
  cout << "$ " << mock1->show() << endl;
  EXPECT_EQ(mock1->show(), "ls -a -l");
  EXPECT_EQ(mock1->run_command(), true);
}

/*
  Test: FailedCommand
  Actual: l -a -l
  Expected Result:
  l is not a command and will fail to run.
  Expected value: FALSE
*/
TEST(CmndTestSet, FailedCommand) {
  Cmnd* mock1 = new Cmnd(4);
  (*mock1)[0] = (char*)"l"; 
  (*mock1)[1] = (char*)"-a"; 
  (*mock1)[2] = (char*)"-l"; 
  (*mock1)[3] = NULL;
  cout << "$ " << mock1->show() << endl;
  EXPECT_EQ(mock1->show(), "l -a -l");
  EXPECT_EQ(mock1->run_command(), false);
}

/*
  Test: ManyArguments
  Actual: echo hello from my program
  Expected Result:
  hello from my program
  Expected value: TRUE
*/
TEST(CmndTestSet, ManyArguments) {
  Cmnd* mock1 = new Cmnd(6);
  (*mock1)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"hello"; 
  (*mock1)[2] = (char*)"from";
  (*mock1)[3] = (char*)"my"; 
  (*mock1)[4] = (char*)"program";
  (*mock1)[5] = NULL;
  cout << "$ " << mock1->show() << endl;
  EXPECT_EQ(mock1->show(), "echo hello from my program");
  EXPECT_EQ(mock1->run_command(), true);
}

/*
  Test: InvalidArgument
  Actual: ls myfile
  Expected Result:
  ERROR: No such file or directory
  Expected value: FALSE
*/
TEST(CmndTestSet, InvalidArgument) {
  Cmnd* mock1 = new Cmnd(3);
  (*mock1)[0] = (char*)"ls"; 
  (*mock1)[1] = (char*)"myfile";
  (*mock1)[2] = NULL;
  cout << "$ " << mock1->show() << endl;
  EXPECT_EQ(mock1->show(), "ls myfile");
  EXPECT_EQ(mock1->run_command(), false);
}

#endif
