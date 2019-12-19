#include "../header/OutputRe_op.hpp"

OutputRe_op::OutputRe_op(int a) :append(a) {}

bool OutputRe_op::run_command() {
  pid_t c_pid;
  int status;

  c_pid =fork();

  if(c_pid ==0) {
    int fd;

    (append)? fd =open((char*)this->right->show().c_str(),O_CREAT |O_APPEND |O_WRONLY,0644)
      :fd =open((char*)this->right->show().c_str(),O_CREAT |O_WRONLY |O_TRUNC,0644);

    if(fd <0) {
      perror("Error");
      exit(1);
    }

    dup2(fd,1);
    close(fd);

    if(!left->run_command()) {}

    exit(1);
  }
  else if(c_pid ==-1) {
    perror("Can not fork");
    exit(-1);
  }
  else {
    wait(&status);
    return true;
  }
}

void OutputRe_op::set_left(Executable* l) {
	this->left =l;
}

void OutputRe_op::set_right(Executable* r) {
	this->right =r;
}

Executable* OutputRe_op::get_left() {
	return this->left;
}

Executable* OutputRe_op::get_right() {
	return this->right;
}

string OutputRe_op::show() {
	if(this->left ==NULL ||this->right ==NULL) {return "OUTPUTRE";}
	if(append) {return this->left->show() +" >> " +this->right->show();}
	return this->left->show() +" > " +this->right->show();
}
