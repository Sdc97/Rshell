#ifndef __TESTCM_TESTS__
#define __TESTCM_TESTS__

#include "gtest/gtest.h"
#include "../header/Test_cm.hpp"

TEST(TestCmTestSet, FirstTest) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-e";
  (*ts)[2] = (char*)"rshell";

  EXPECT_EQ(ts->run_command(), true);
}

TEST(TestCmTestSet, DefaultFlag) {
  Test_cm* ts = new Test_cm(3);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"unit_tests";

  EXPECT_EQ(ts->run_command(), true);
}

TEST(TestCmTestSet, DefaultFail) {
  Test_cm* ts = new Test_cm(3);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"notsrc";

  EXPECT_EQ(ts->run_command(), false);
}

TEST(TestCmTestSet, NotADirectory) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-d";
  (*ts)[2] = (char*)"test";

  EXPECT_EQ(ts->run_command(), false);
}

TEST(TestCmTestSet, DirectoryExists) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-d";
  (*ts)[2] = (char*)"header/";

  EXPECT_EQ(ts->run_command(), true);
}

TEST(TestCmTestSet, DirectoryDNE) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-d";
  (*ts)[2] = (char*)"somewhere";

  EXPECT_EQ(ts->run_command(),false);
}

TEST(TestCmTestSet, NotARegFile) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-f";
  (*ts)[2] = (char*)"src";

  EXPECT_EQ(ts->run_command(), false);
}

TEST(TestCmTestSet, RegularFile) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-f";
  (*ts)[2] = (char*)"names.txt";

  EXPECT_EQ(ts->run_command(), true);
}

TEST(TestCmTestSet, NotAFile) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-f";
  (*ts)[2] = (char*)"somewhere";

  EXPECT_EQ(ts->run_command(),false);
}

TEST(TestCmTestSet, eTagPass) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-e";
  (*ts)[2] = (char*)"src";

  EXPECT_EQ(ts->run_command(), true);
}

TEST(TestCmTestSet, eTagExecutable) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-e";
  (*ts)[2] = (char*)"test";

  EXPECT_EQ(ts->run_command(), true);
}

TEST(TestCmTestSet, eTagNotAFile) {
  Test_cm* ts = new Test_cm(4);
  (*ts)[0] = (char*)"test";
  (*ts)[1] = (char*)"-e";
  (*ts)[2] = (char*)"somewhere";

  EXPECT_EQ(ts->run_command(),false);
}

#endif
