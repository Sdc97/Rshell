#ifndef __PIPE_TESTS__
#define __PIPE_TESTS__

#include "gtest/gtest.h"
#include "../header/Pipe_op.hpp"
#include "../header/Cmnd.hpp"

TEST(PipeOpTestSet, FirstTest) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(4);
  (*mock1)[0] = (char*)"echo";
  (*mock1)[1] = (char*)"first";
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"tr";
  (*mock2)[1] = (char*)"a-z";
  (*mock2)[2] = (char*)"A-Z";
  (*mock2)[3] = NULL;
  Pipe_op* con = new Pipe_op();
  con->set_left(mock1);
  con->set_right(mock2);
  EXPECT_EQ(con->run_command(), true);
}

TEST(PipeOpTestSet, FirstCommandFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(4);
  (*mock1)[0] = (char*)"ech";
  (*mock1)[1] = (char*)"first";
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"tr";
  (*mock2)[1] = (char*)"a-z";
  (*mock2)[2] = (char*)"A-Z";
  (*mock2)[3] = NULL;
  Pipe_op* con = new Pipe_op();
  con->set_left(mock1);
  con->set_right(mock2);
  EXPECT_EQ(con->run_command(), false);
}

TEST(PipeOpTestSet, SecondCommandFail) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(4);
  (*mock1)[0] = (char*)"echo";
  (*mock1)[1] = (char*)"first";
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"t";
  (*mock2)[1] = (char*)"a-z";
  (*mock2)[2] = (char*)"A-Z";
  (*mock2)[3] = NULL;
  Pipe_op* con = new Pipe_op();
  con->set_left(mock1);
  con->set_right(mock2);
  EXPECT_EQ(con->run_command(), false);
}

TEST(PipeOpTestSet, NoNeededInput) {
  Cmnd* mock1 = new Cmnd(3);
  Cmnd* mock2 = new Cmnd(2);
  (*mock1)[0] = (char*)"echo";
  (*mock1)[1] = (char*)"first";
  (*mock1)[2] = NULL;
  (*mock2)[0] = (char*)"pwd";
  (*mock2)[1] = NULL;
  Pipe_op* con = new Pipe_op();
  con->set_left(mock1);
  con->set_right(mock2);
  EXPECT_EQ(con->run_command(), true);
}

TEST(PipeOpTestSet, NoOutput) {
  Cmnd* mock1 = new Cmnd(2);
  Cmnd* mock2 = new Cmnd(2);
  (*mock1)[0] = (char*)"echo";
  (*mock1)[1] = NULL;
  (*mock2)[0] = (char*)"tee";
  (*mock2)[1] = NULL;
  Pipe_op* con = new Pipe_op();
  con->set_left(mock1);
  con->set_right(mock2);
  EXPECT_EQ(con->run_command(), true);
}
#endif
