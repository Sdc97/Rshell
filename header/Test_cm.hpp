#ifndef __TEST_CMND__
#define __TEST_CMND__

#include "Executable.hpp"
#include "Cmnd.hpp"
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

using namespace std;

class Test_cm : public Cmnd {
private:
  //Available flags:
  // -e 0, -f 1, -d 2
  int flag = 0;
  char* path;
  string flgs[3] = {"-e","-f","-d"};
  void setFlag() { // Sets flag to 0,1,2 if it finds a flag
    bool found = false;
    for(int i = 0; i < SIZE-1 && !found; i++) {
      for(int j = 0; j < 3; j++) {
	if(!strcmp(command[i],flgs[j].c_str())) {
	  flag = j;
	  found = true;
	}
      }
    }
    if(!found) { //If no flag found, assume file is at pos 1
      path = command[1];
    } else { // Else file is at pos 2
      path = command[2];
    }
  }
public:
  Test_cm(int s) : Cmnd(s) { }
  bool run_command() {
    setFlag();
    struct stat st;
    int status = stat(path,&st);
    if(status == -1) {
      cout << "(FALSE)" << endl;
      return false;
    }
    if(flag == 0) {
      cout << "(TRUE)" << endl;
      return true;
    }
    if(flag == 1) {
      if(S_ISREG(st.st_mode) != 0) {
	cout << "(TRUE)" << endl;
	return true;
      } else {
	cout << "(FALSE)" << endl;
	return false;
      }
    }
    if(flag == 2) {
      if(S_ISDIR(st.st_mode) != 0) {
	cout << "(TRUE)" << endl;
	return true;
      } else {
	cout << "(FALSE)" << endl;
	return false;
      }
    }
  }
  
};

#endif
