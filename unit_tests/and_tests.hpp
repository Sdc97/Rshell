#ifndef __AND_TESTS__
#define __AND_TESTS__

#include "../header/Executable.hpp"
#include "../header/And_op.hpp"
#include "../header/Or_op.hpp"
#include "../mocks/cmnd_mock.hpp"
#include "../header/Cmnd.hpp"

#include "gtest/gtest.h"

class Cmnd;

/* 
   Mock Tests
   Should return the following values:
   true && true = true
   true && false = false
   false && true = false
   false && false = false
*/
TEST(AndOpTestSet, MockTest1) {
  Executable* mock1 = new Cmnd_mock(true);
  Executable* mock2 = new Cmnd_mock(true);

  Executable* first = new And_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

TEST(AndOpTestSet, MockTest2) {
  Executable* mock1 = new Cmnd_mock(true);
  Executable* mock2 = new Cmnd_mock(false);

  Executable* first = new And_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), false);
}

TEST(AndOpTestSet, MockTest3) {
  Executable* mock1 = new Cmnd_mock(false);
  Executable* mock2 = new Cmnd_mock(true);

  Executable* first = new And_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), false);
}

TEST(AndOpTestSet, MockTest4) {
  Executable* mock1 = new Cmnd_mock(false);
  Executable* mock2 = new Cmnd_mock(false);

  Executable* first = new And_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), false);
}

/* 
   Test: TwoPassCmnd
   Actual: echo first && echo second
   Expected Result:
   first
   second
   Expected Value: TRUE
*/
TEST(AndOpTestSet, TwoPassCmnd) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo";
  (*mock2)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new And_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

/* 
   Test: FirstFail
   Actual: ech first && echo second
   Expected Result:
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, FirstFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech";
  (*mock2)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new And_op(mock1,mock2);
  cout << first->show() << endl;
  EXPECT_EQ(first->run_command(), false);
}

/* 
   Test: SecondFail
   Actual: echo first && ech second
   Expected Result:
   first
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, SecondFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo";
  (*mock2)[0] = (char*)"ech"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new And_op(mock1,mock2);
  cout << first->show() << endl;
  EXPECT_EQ(first->run_command(), false);
}

/* 
   Test: BothFail
   Actual: ech first && ech second
   Expected Result:
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, BothFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech";
  (*mock2)[0] = (char*)"ech"; 
  (*mock1)[1] = (char*)"First Pass";
  (*mock2)[1] = (char*)"HELLO"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new And_op(mock1,mock2);
  cout << first->show() << endl;
  EXPECT_EQ(first->run_command(), false);
}

/* 
   Test: AndFailThenOr
   Actual: echo first || ech second && echo third
   Expected Result:
   first
   third
   Expected Value: TRUE
*/
TEST(AndOpTestSet, OrPassAndPass) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"ech";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"echo";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), true);
}

/* 
   Test: OrPassAndFail
   Actual: echo first || echo second && ech third
   Expected Result:
   first
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, AndPassThenOr) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"echo";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"ech";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), false);
}

/* 
   Test: OrFailThenAndFail
   Actual: ech first || ech second && ech third
   Expected Result:
   ERROR
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, OrFailThenAndFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"ech";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"ech";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), false);
}

/* 
   Test: TwoAndLastFail
   Actual: echo first && echo second && ech third
   Expected Result:
   first
   second
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, TwoAndLastFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"echo";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"ech";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new And_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), false);
}

/* 
   Test: TwoAndMiddleFail
   Actual: echo first && ech second && echo third
   Expected Result:
   first
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, TwoAndMiddleFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"ech";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"echo";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new And_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), false);
}

/* 
   Test: TwoAndFirstFail
   Actual: ech first && echo second && echo third
   Expected Result:
   ERROR
   Expected Value: FALSE
*/
TEST(AndOpTestSet, TwoAndFirstFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"echo";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"echo";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new And_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), false);
}

/* 
   Test: TwoAndAllPass
   Actual: echo first && echo second && echo third
   Expected Result:
   first
   second
   third
   Expected Value: TRUE
*/
TEST(AndOpTestSet, TwoAndAllPass) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"echo";
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"echo";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new And_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), true);
}

/* 
   Test: DifferentCommands
   Actual: ls header && pwd && echo third
   Expected Result:
   *Directory listing of header/
   *Working directory
   third
   Expected Value: TRUE
*/
TEST(AndOpTestSet, DifferentCommands) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(2);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"ls"; 
  (*mock1)[1] = (char*)"header";  
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"pwd";
  (*mock2)[1] = NULL;
  (*mock3)[0] = (char*)"echo";
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new And_op(mock1,mock2);
  Executable* second = new And_op(first,mock3);
  cout << second->show() << endl;
  EXPECT_EQ(second->run_command(), true);
}
#endif
