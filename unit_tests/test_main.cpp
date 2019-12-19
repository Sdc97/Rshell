#include "gtest/gtest.h"

#include "and_tests.hpp"
#include "or_tests.hpp"
#include "cmnd_tests.hpp"
#include "parser_tests.hpp"
#include "testcm_tests.hpp"
#include "outputRe_tests.hpp"
#include "inputRe_tests.hpp"
#include "pipe_tests.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
