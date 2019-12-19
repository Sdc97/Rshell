#include "../header/InputRe_op.hpp"

InputRe_op::InputRe_op() {}

bool InputRe_op::run_command() {
	pid_t c_pid;
	int status;

	c_pid =fork();

	if(c_pid ==0) {
		int fd;
		fd =open((char*)this->right->show().c_str(), O_RDONLY,0644);

		if(fd <0) {
			perror("ERROR");
			exit(1);
		}

		dup2(fd,0);
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
void InputRe_op::set_left(Executable* l) {
	this->left =l;
}

void InputRe_op::set_right(Executable* r) {
	this->right =r;
}

Executable* InputRe_op::get_left() {
	return this->left;
}

Executable* InputRe_op::get_right() {
	return this->right;
}

string InputRe_op::show() {
	if(this->left ==NULL ||this->right ==NULL) {return "INPUTRE";}
	return this->left->show() + " < " + this->right->show();
}
