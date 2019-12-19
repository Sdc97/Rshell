#include "../header/And_op.hpp"

And_op::And_op(Executable* l, Executable* r) {
    left =l;
    right =r;
}

And_op::And_op() {}

bool And_op::run_command() {
  if(!left->run_command()) {
    return false;
  }
  if(!right->run_command()) {
    return false;
  }
  return true;
}

void And_op::set_left(Executable* l) {
	this->left =l;
}

void And_op::set_right(Executable* r) {
	this->right =r;
}

Executable* And_op::get_left() {
    return left;
}

Executable* And_op::get_right() {
    return right;
}

string And_op::show() {
  if(left ==NULL ||right ==NULL) {return "AND";}
  return left->show() + " && " + right->show();
}
