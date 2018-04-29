#include "conditions.h"

using namespace std;


Conditions::Conditions(string conds){
	this->conditions = new vector<Condition*>();
	this->ops = new vector<string>();
	if(conds.find(' ') == string::npos){
		this->conditions->push_back(new Condition(conds));
	}else{
		vector<string>* args = c_explode(' ',conds);
		for(int i = 0;i < args->size();i++){
			if(i % 2 == 0){
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
		
string Conditions::toCpp(string var,string var2,vector<string>* select_columns,vector<Column*>* columns){
	string out = this->conditions->at(0)->toCpp(var,var2,select_columns,columns);
	for(int i = 1;i<this->conditions->size();i++){
		out += " " + this->ops->at(i - 1) + " " + this->conditions->at(i)->toCpp(var,var2,select_columns,columns);
	}
	return out;
}


vector<Conditions*>* Conditions::getConditions(vector<string>* cond){
	if(cond == nullptr || cond->size() == 0){
		return nullptr;
	}else if(cond->size() == 1){
		cout<<"First cond: "<<cond->at(0)<<endl;
	}else{
		cout<<"Cond size is "<<cond->size()<<endl;
	}
	vector<Conditions*>* out = new vector<Conditions*>();
	for(auto it = cond->begin();it != cond->end(); it++){
		out->push_back(new Conditions(*it));
	}
	return out;
}