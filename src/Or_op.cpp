#include "../header/Or_op.hpp"

Or_op::Or_op(Executable* l, Executable* r) {
    this->left =l;
    this->right =r;
}

Or_op::Or_op() {}

bool Or_op::run_command() {
  if(left->run_command()) {
    return true;
  } else {
    return right->run_command();
  }
}

void Or_op::set_left(Executable* l) {
	this->left =l;
}

void Or_op::set_right(Executable* r) {
	this->right =r;
}

Executable* Or_op::get_left() {}

Executable* Or_op::get_right() {}

string Or_op::show() {
  if(left == NULL ||right ==NULL) {return "";}
  return left->show() + " || " + right->show(); 
}
