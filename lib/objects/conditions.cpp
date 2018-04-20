#include "conditions.h"

using namespace std;


Conditions::Conditions(string conds){
	this->conditions = new vector<Condition*>();
	this->ops = new vector<string>();
	if(conds.find(' ') == string::npos){
		this->conditions->push_back(new Condition(conds));
	}else{
		vector<string>* args = c_explode(' ',conds);
		for(int i = 0;i<args->size();i++){
			if(i%2 == 0){
				this->conditions->push_back(new Condition(args->at(i)));
			}else{
				this->ops->push_back(args->at(i));
			}
		}
	}
	
}

Conditions::~Conditions(){
	delete this->conditions;
	delete this->ops;
}
		
string Conditions::toCpp(string var){
	string out = var + "->" + this->conditions->at(0)->toCpp();
	for(int i = 1;i<this->conditions->size();i++){
		out += " " + this->ops->at(i - 1) + " " + var + "->" + this->conditions->at(i)->toCpp();
	}
	return out;
}


vector<Conditions*>* Conditions::getConditions(vector<string>* cond){
	vector<Conditions*>* out = new vector<Conditions*>();
	for(auto it = cond->begin();it != cond->end(); it++){
		out->push_back(new Conditions(*it));
	}
	return out;
}