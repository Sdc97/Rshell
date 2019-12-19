CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(rshell)

ADD_SUBDIRECTORY(googletest)

set(HEADERS header/Cmnd.hpp header/And_op.hpp header/Or_op.hpp header/Executable.hpp header/Parser.hpp)
set(SOURCES src/main.cpp src/Cmnd.cpp src/And_op.cpp src/Or_op.cpp src/Parser.cpp src/OutputRe_op.cpp src/Pipe_op.cpp src/InputRe_op.cpp)
set(TESTING unit_tests/test_main.cpp src/And_op.cpp src/Or_op.cpp src/Cmnd.cpp src/Parser.cpp src/OutputRe_op.cpp src/Pipe_op.cpp src/InputRe_op.cpp)

set(MOCKFILES mocks/cmnd_mock.hpp) 

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
   ${SOURCES}
)

ADD_EXECUTABLE(test
   ${HEADERS} ${TESTING} ${MOCKFILES} 
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
