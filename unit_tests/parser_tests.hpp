#ifndef PARSER_TEST
#define PARSER_TEST

#include "gtest/gtest.h"
#include "../header/Parser.hpp"

TEST(ParserTestSet, singleCommand) {
	Parser p("echo \"hello\";");
	EXPECT_EQ(p.showCmnd(0),"echo hello");
}

TEST(parserTestSet, commandWithConnector) {
	Parser a("echo hello && echo bye;");
	EXPECT_EQ(a.showCmnd(0), "echo hello && echo bye");
}

TEST(parserTestSet, commandWithComment) {
	Parser b("echo #hello");
	EXPECT_EQ(b.showCmnd(0), "echo");
}

TEST(parserTestSet, cmake) {
	Parser c("cmake3 .;");
	EXPECT_EQ(c.showCmnd(0), "cmake3 .");
}

TEST(parserTestSet, commandWithConnector1) {
	Parser d("test -e rshell || echo \"NOT HERE\"");
	EXPECT_EQ(d.showCmnd(0), "test -e rshell || echo NOT HERE");
}

TEST(parserTestSet, longCommand) {
	Parser e("ls -a; echo hello && mkdir test || echo world; git status;");
	EXPECT_EQ(e.showCmnd(0), "ls -a");
	EXPECT_EQ(e.showCmnd(1), "echo hello && mkdir test || echo world");
	EXPECT_EQ(e.showCmnd(2), "git status");
}

TEST(parserTestSet, superEdgeCase) {
	Parser f("echo \"there is a comment # in this quote\"; echo \"We got here?!?!?\"");
	EXPECT_EQ(f.showCmnd(0), "echo there is a comment # in this quote");
	EXPECT_EQ(f.showCmnd(1), "echo We got here?!?!?");
}

TEST(parserTestSet, please) {
	Parser g("echo we definitely deserve 100% on this assignment; echo please; echo please");
	EXPECT_EQ(g.showCmnd(0), "echo we definitely deserve 100% on this assignment");
	EXPECT_EQ(g.showCmnd(1), "echo please");
	EXPECT_EQ(g.showCmnd(2), "echo please");
}
#endif
