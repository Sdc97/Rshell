#include "../header/Cmnd.hpp"
#include <limits.h>

Cmnd::Cmnd(int size) : SIZE(size) {
    command =new char*[SIZE];
}

Cmnd::~Cmnd() {
    delete []command;
}

char* &Cmnd::operator [](int i) {
    if(i >= this->SIZE) {
        cout <<"Input greater than SIZE" <<endl;
        exit(-1);
    }
    return command[i];
}

bool Cmnd::run_command() {
  //cout << command[0] << endl;
    pid_t c_pid;
    int status;
    int fd[2];
    pipe(fd);
    c_pid =fork();
    
    if(c_pid ==0) {
      dup2(fd[1],STDOUT_FILENO);
      close(fd[1]);
      close(fd[0]);
	if(execvp(command[0], command) ==-1) {
	  perror("ERROR");
	}
	_exit(1);
    }
    else if(c_pid ==-1) {
	perror("Can not fork");
	exit(-1);
    }
    else { 
      wait(&status);
      close(fd[1]);
      char buffer[4096];
      int count = 0;
      do {
	count = read(fd[0], buffer, sizeof(buffer));
	if (count == -1) {
	  if (errno == EINTR) {
	    cout << "Continuing" << endl;
	    continue;
	  }
	} else if( count != 0){
	  for(int i = 0; i < count; i++) {
	    cout << buffer[i];
	  }
	}
      } while( count != 0);
      return (!status);
    }
}

const int Cmnd::get_size() {
	return this->SIZE;
}

void Cmnd::set_left(Executable* l) {}
void Cmnd::set_right(Executable* r) {}

string Cmnd::show() {
  string s = "";
    for(int i =0; i <this->SIZE-1; i++) {
      s += this->command[i];
      if(i != SIZE-2)
	s += " ";
    }
    return s;
}
