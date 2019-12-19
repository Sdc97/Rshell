#include "../header/Parser.hpp"
#include <unistd.h>

Executable* Parser::create(string s) {
    	Cmnd* cmnd =nullptr;
	string *l =nullptr;		//To store the parsed command
	bool quote0 =0;			//To indicate there is quote in the command
	bool ignore = 0;
	int k =0;			//Used to assign the last index of char array command to NULL

	if(s.substr(0,4) =="exit") {
		return new Exit_cm(2);
	}

	else if(s.substr(0,4) =="test") {
	  cmnd =new Test_cm(count(s));
	}

	else {
		cmnd =new Cmnd(count(s));
	}
        l =new string();

	for(int i =0; i <s.length(); i++) {
	  
	  if(s[i] == '"') {
            if(s[i-1] == 92) {
	      s.erase(i-1,1);
	      l->erase(l->length()-1,1);
	      i--;
	    } else {
	      quote0 = !quote0;
	      s.erase(i,1);
	      i--;
	      ignore = true;
	    }
	  }
	  
	  else if(s[i] ==' ' &&!quote0) {
            (*cmnd)[k] =(char*)(*l).c_str();
	    l =new string();
	    k++;
	    continue;
	  }

	  if(!ignore) {
	    (*l) += s[i];
	  } else {
	    ignore = false;
	  }

	  if(i >=s.length()-1) {
	    (*cmnd)[k] =(char*)(*l).c_str();
	    k++;
	    continue;
	  }
	}
	(*cmnd)[k] =NULL;

	return cmnd;
}

int Parser::count(string s) {
	bool quote1 =false;
	int counter =0;
	for(int i =0; i <s.length(); i++) {
		if(s[i] =='"' &&s[i-1] !=92) {quote1 =!quote1;}	//if s[i] =='"' and s[i-1] !='\' then invert quote1 to indicate there is a quote
		if((s[i] ==' ' &&!quote1) ||i ==s.length()-1) {counter++;}
	}
	return ++counter;
}
			
void Parser::precheck(string &s) {
	if(s.length() <1) {return;}
	int parenthesis =0;

	for(int i =0; i <s.length(); i++) {
	    if(s[i] =='(' && !quote) parenthesis++;
	    if(s[i] ==')' && !quote) parenthesis--;
		if(s[i] =='[') {
			s.erase(i,1);
			s.insert(i,"test ");
		}
		if(s[i] ==']') {
			s.erase(i,1);
			i--;
		}
		if(s[i] =='"' && s[i-1] !=92) {quote =!quote;}	//if s[i] =='"' and s[i-1] !='\' invert quote to indicate there is quote
		if(s[i] =='#' && !quote) {
			s.erase(s.begin()+i, s.end());		//erase the '#' and whatever is after it
			break;
		}
		if(s[i] ==' ' && !quote) {
			if(s[i+1] ==' ' ||i-1 <=0 ||i ==s.length()-1 ||s[i+1] =='&' ||s[i+1] =='|' ||s[i+1] ==';' ||s[i+1] =='('
			   ||s[i+1] ==')' ||s[i+1] =='[' ||s[i+1] ==']' ||s[i+1] =='>' ||s[i+1] =='#' ||s[i+1] =='<'
			   ||s[i-1] =='&' ||s[i-1] =='|' ||s[i-1] ==';' ||s[i-1] ==';' ||s[i-1] =='(' ||s[i-1] ==')'
			   ||s[i-1] =='[' ||s[i-1] ==']' ||s[i-1] =='#' ||s[i-1] =='>' ||s[i-1] =='<') {
				s.erase(i,1);			//erase the space in between connectors and #'s
				i--;				//relocate the index to the current index
			}
		}
		try {
		if(parenthesis < 0) {
			throw parenthesis;
		}	
		}
		catch (int x) {
		  cout <<"ERROR: odd (" <<x <<") number of parenthesis" <<endl;
		  s.clear();
		  return;
		}
	}

	if(s.length() ==0) {
		return;
	}
	try {
		if(parenthesis !=0) {
			throw parenthesis;
		}	
	}
	catch (int x) {
		cout <<"ERROR: odd (" <<x <<") number of parenthesis" <<endl;
		s.clear();
		return;
	}
	(s[s.length()-1] !=';') ? (s +=";"): s;
	quote =false;
}

void Parser::preCreate(string s) {
	int l =0;	//holds the first index of the first character in command
	bool quote =false;
	vector<Executable*> tempHold;
	for(int i =0; i <s.length(); i++) {
	  int j = 0;
	  if(s[i] =='"' &&s[i-1] !=92) {quote =!quote;}
	  for(j = 0; j < connectors.length() && !quote; j++) {
	    if(s[i] == connectors[j])
	      break;
	  }

	  if(!quote && j < connectors.length()) { //is a connector
	    if(s.substr(l,i-l).length() > 0) {
	      tempHold.push_back(create(s.substr(l,i-l)));
	    }
	    switch(connectors[j]) {
	    case '&':
	      tempHold.push_back(new And_op());
	      l = i+2;
	      i++;
	      break;
	    case '|': // Will need to be modified for piping to check for double or single |
	      if(s[i+1] == '|') { tempHold.push_back(new Or_op()); l = i+2; i++; }
	      else {tempHold.push_back(new Pipe_op()); l = i + 1; i++; }
	      break;
	    case '(':
	      tempHold.push_back(new Parentheses(connectors[j]));
	      l = i + 1;
	      break;
	    case ')':
	      tempHold.push_back(new Parentheses(connectors[j]));
	      l = i + 1;
	      break;
	    case '<':
	      tempHold.push_back(new InputRe_op());
	      l = i + 1;
	      break;
	    case '>':
	      if(s[i+1] =='>') {tempHold.push_back(new OutputRe_op(1)); l = i + 2; i++;}
	      else {tempHold.push_back(new OutputRe_op(0)); l = i + 1; i++;}
	      break;
	    case ';':
	      l = i + 1;
	      /*for(int z = 0; z < tempHold.size(); z++)
		cout << tempHold[z]->getType() << " ";
	      cout << endl;
	      */
	      if(tempHold.size() > 0 && (tempHold[0]->getType() == "CMND" || tempHold[0]->getType() == "("))
		exe.push_back(process(tempHold));
	      tempHold.clear();
	      break;
	    }
	  }
	}
}

bool Parser::priority(Executable* f, Executable* s) {
  string x = f->getType();
  string y = s->getType();
  //cout << x << " " << y << endl;
  int a,b;
  if(x == "AND" || x == "OR")
    a = 1;
  else
    a = 2;
  if(y == "AND" || y == "OR")
    b = 1;
  else 
    b = 2;
  return b <= a;
}

Executable* Parser::process(vector<Executable*> con) {
  int i = 0;
  deque<Executable*> output; // "Output "Queue" "
  deque<Executable*> operators; // "Operator stack"
  /*
  for(int j = 0; j < con.size(); j++) {
    cout << con[j]->getType() << " ";
  }
  cout << endl;
  */
  while(i < con.size()) {
    Executable* curr = con[i];
    /*
    cout << "Current is : " << i << endl;
    for(int j = 0; j < output.size(); j++) {
      cout << output[j]->getType() << " ";
    }
    cout << endl;
    for(int j = 0; j < operators.size(); j++) {
      cout << operators[j]->getType() << " ";
    }
    cout << endl;
    */
    if(curr->getType() == "CMND") {
      output.push_front(curr);
    } 
    else if (curr->getType() == "AND" || curr->getType() == "OR" ||curr->getType() == "OUTPUTRE" || curr->getType() =="INPUTRE" || curr->getType() == "PIPE") {
      while((!operators.empty() && priority(operators.front(),curr)) && operators.front()->getType() != "(") {
	Executable* tm = operators.front();
	operators.pop_front();
	tm->set_right(output.front());
	output.pop_front();
	tm->set_left(output.front());
	output.pop_front();
	output.push_front(tm);
      }
      operators.push_front(curr);
    } else if (curr->getType() == "(") {
      operators.push_front(curr);
    } else if (curr->getType() == ")") {
      while(operators.front()->getType() != "(") {
	Executable* tm = operators.front();
	operators.pop_front();
	tm->set_right(output.front());
        output.pop_front();
	tm->set_left(output.front());
        output.pop_front();
	output.push_front(tm);
      }
      operators.pop_front();
    }
    
    i++;
  }
  /*
  for(int j = 0; j < output.size(); j++) {
    cout << output[j]->getType() << " ";
  }
  cout << endl;
  for(int j = 0; j < operators.size(); j++) {
    cout << operators[j]->getType() << " ";
  }
  cout << endl;
  */ 
  while(!operators.empty()) {
    Executable* tm = operators.front();
    operators.pop_front();
    tm->set_right(output.front());
    output.pop_front();
    tm->set_left(output.front());
    output.pop_front();
    output.push_front(tm);
  }
  if(output.size() == 1) {
    return output.front();
  }
  else {
    return NULL;
  }
}


Parser::Parser(string s) {
	precheck(s);
	preCreate(s);

	run();
}
void Parser::run() {
	for(int i =0; i <exe.size(); i++) {
	  if(exe[i] != NULL) {
	    exe[i]->run_command();
	    //cout << exe[i]->getType() << endl;
	  }
	}
}
string Parser::showCmnd(int i) {
	return exe[i]->show();
}

Parser::~Parser() {
	for(int i =0; i <exe.size(); i++) {
		delete exe[i];
	}
}
