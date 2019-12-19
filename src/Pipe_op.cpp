#include "../header/Pipe_op.hpp"

Pipe_op::Pipe_op() { }

bool Pipe_op::run_command() {
  //cout << "HERE" << endl;
  int pds[2];
  pipe(pds);
  pid_t pid = fork(); 
  if(pid == 0) {
    dup2(pds[1],1);
    if(left->run_command()) { _exit(EXIT_SUCCESS); }
    _exit(EXIT_FAILURE);
  } else {
    int status;
    waitpid(pid,&status,0);
    if(WIFEXITED(status)) { 
      int st = WEXITSTATUS(status);
      if(st != 0)
	return false;
    } else {
      return false;
    }
    int save = dup(0);
    dup2(pds[0],0);
    close(pds[1]);
    if(!right->run_command()) { 
      dup2(save,0);
      return false; 
    }
    dup2(save,0);
    return true;
  }
}

void Pipe_op::set_left(Executable* l) {
  this->left =l;
}

void Pipe_op::set_right(Executable* r) {
  this->right =r;
}

Executable* Pipe_op::get_left() {
  return this->left;
}

Executable* Pipe_op::get_right() {
  return this->right;
}

string Pipe_op::show() {
  if(this->left ==NULL ||this->right ==NULL) {return "PIPE";}
  return this->left->show() +" | " +this->right->show();
}
