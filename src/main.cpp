#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <limits.h>

using namespace std;

#include "../header/Parser.hpp"

int main() {
	string cmnd ="";
	do {
		cout <<char(36) << " ";
		getline(cin, cmnd);
		Parser parse(cmnd);
	}while(true);
	return 0;
}
