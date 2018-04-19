#include "condition.h"

using namespace std;
//1.state='NY'

Condition::Condition(string cond){
	string tmp = cond;
	if(tmp.find('.')!=string::npos){
		vector<string>* s = split('.',tmp);
		this->group = stoi(s->at(0));
		tmp = s->at(1);
		delete s;
	}else{
		this->group = 0;
	}
	int index = strpos_m(tmp,3,string("="),string("<"),string(">") );
	this->column = tmp.substr(0,index);
	if(index == -1){
		throw "Error, invalid Condition";
	}else if(index == strpos_m(tmp,2,string("<="),string(">="))){
		this->exp = tmp.substr(index,2);
		tmp = tmp.substr(index+2);
	}else{
		this->exp = tmp.substr(index,1);
		tmp = tmp.substr(index + 1);
	}
	this->value = str_replace("'","\"",tmp);
}

string Condition::toCpp(){
	string out = this->column;
	if(this->value.find("\"") != string::npos){
		out += ".compare("+this->value+") == 0";
	}else{
		out += " == " + this->value;
	}
	return out;
}


