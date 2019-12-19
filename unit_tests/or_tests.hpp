#ifndef __OR_TESTS__
#define __OR_TESTS__

#include "../header/Executable.hpp"
#include "../mocks/cmnd_mock.hpp"
#include "../header/Or_op.hpp"
#include "../header/And_op.hpp"
#include "../header/Cmnd.hpp"

using namespace std;

TEST(OrOpTestSet, MockTest1) {
  Executable* mock1 = new Cmnd_mock(true);
  Executable* mock2 = new Cmnd_mock(true);

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

TEST(OrOpTestSet, MockTest2) {
  Executable* mock1 = new Cmnd_mock(true);
  Executable* mock2 = new Cmnd_mock(false);

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

TEST(OrOpTestSet, MockTest3) {
  Executable* mock1 = new Cmnd_mock(false);
  Executable* mock2 = new Cmnd_mock(true);

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

TEST(OrOpTestSet, MockTest4) {
  Executable* mock1 = new Cmnd_mock(false);
  Executable* mock2 = new Cmnd_mock(false);

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), false);
}

/* 
   Test: FirstPassCmnd
   Actual: echo first || echo second
   Expected Result:
   first
   Expected Value: TRUE
*/
TEST(OrOpTestSet, TwoPassCmnd) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo";
  (*mock2)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

/* 
   Test: FirstPassCmnd
   Actual: echo first || ech second
   Expected Result:
   first
   Expected Value: TRUE
*/
TEST(OrOpTestSet, FirstPassCmnd) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo";
  (*mock2)[0] = (char*)"ech"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

/* 
   Test: SecondPassCmnd
   Actual: ech first || echo second
   Expected Result:
   ERROR
   second
   Expected Value: TRUE 
*/
TEST(OrOpTestSet, SecondPassCmnd) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech";
  (*mock2)[0] = (char*)"echo"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), true);
}

/* 
   Test: BothFailCmnd
   Actual: ech first || ech second
   Expected Result:
   ERROR
   ERROR
   Expected Value: FALSE 
*/
TEST(OrOpTestSet, BothFailCmnd) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech";
  (*mock2)[0] = (char*)"ech"; 
  (*mock1)[1] = (char*)"first";
  (*mock2)[1] = (char*)"second"; 
  (*mock1)[2] = NULL;
  (*mock2)[2] = NULL; 

  Executable* first = new Or_op(mock1,mock2);

  EXPECT_EQ(first->run_command(), false);
}

/* 
   Test: AndPassThenOr
   Actual: echo first && echo second || echo third
   Expected Result:
   first
   second
   Expected Value: TRUE 
*/
TEST(OrOpTestSet, AndPassThenOr) {
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
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), true);
}

/* 
   Test: AndFailOrFail
   Actual: echo first && ech second || ech third
   Expected Result:
   first
   ERROR
   ERROR
   Expected Value: FALSE 
*/
TEST(OrOpTestSet, AndFailOrFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"echo";
  (*mock1)[1] = (char*)"first"; 
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"ech"; 
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"ech"; 
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new And_op(mock1,mock2);
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), false);
}

/* 
   Test: AndFailOrPass
   Actual: echo first && ech second || echo third
   Expected Result:
   first
   ERROR
   third
   Expected Value: TRUE 
*/
TEST(OrOpTestSet, AndFailOrPass) {
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
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), true);
}

// Test: TwoOrPass
// Actual: echo first || echo second || echo third
// Expected Result: "first" will print.
// TRUE
TEST(OrOpTestSet, TwoOrPass) {
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

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), true);
}

// Test: FirstOrSecondPass
// Actual: ech first || echo second || echo third
// Expected Result: One error message will print. Then "second".
// TRUE
TEST(OrOpTestSet, FirstOrSeocondPass) {
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

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), true);
}

// Test: SecondOrLastPass
// Actual: ech first || ech second || echo third
// Expected Result: Two error messages will print. Then "third".
// TRUE
TEST(OrOpTestSet, SecondOrLastPass) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(3);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"ech";
  (*mock1)[1] = (char*)"first"; 
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"ech"; 
  (*mock2)[1] = (char*)"second";
  (*mock2)[2] = NULL;
  (*mock3)[0] = (char*)"echo"; 
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), true);
}

// Test: AllOrFail
// Actual: ech first || ech second || ech third
// Expected Result: Three error messages will print.
// FALSE
TEST(OrOpTestSet, AllOrFail) {
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
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), false);
}

// Test: DifferentCommands
// Actual: ls header || pwd || echo third
// Expected Result: Listing of header directory.
// TRUE
TEST(OrOpTestSet, DifferentCommands) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(2);
  Cmnd* mock3 = new Cmnd(3);
  (*mock1)[0] = (char*)"ls";
  (*mock1)[1] = (char*)"-a"; 
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"pwd"; 
  (*mock2)[1] = NULL;
  (*mock3)[0] = (char*)"echo"; 
  (*mock3)[1] = (char*)"third";
  (*mock3)[2] = NULL;  

  Executable* first = new Or_op(mock1,mock2);
  Executable* second = new Or_op(first,mock3);
  EXPECT_EQ(second->run_command(), true);
}

#endif
