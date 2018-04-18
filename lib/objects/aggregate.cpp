#include "aggregate.h"

using namespace std;


Aggregate::Aggregate(string aggr){
	vector<string>* data = c_explode('_',aggr);
	if(data->size() == 3){
		this->group = atoi(data->at(0).c_str());
		this->func = data->at(1);
		this->column = data->at(2);
	}else{
		this->group = 0;
		this->func = data->at(0);
		this->column = data->at(1);
	}
	
	delete data;
}

Aggregate::~Aggregate(){

}

string Aggregate::toESQL(){
	string out = this->func + "(";
	out.append(itoa(this->group));
	out += "." + this->column + ")";
	return out;
}

string Aggregate::toSQL(){
	return this->func + "("+this->column + ")";
}

string Aggregate::toString(){
	string out;
	if(this->group != 0){
		out.append(itoa(this->group));
		out += "_";
	}
	out += this->func + "_" + this->column;
	return out;
}

string Aggregate::toABSVar(){
	string out("");
	out += this->func + "_" + this->column;	
	if(this->group != 0){
		out += "_";
		out.append(itoa(this->group));
	}
	return out;
}

string Aggregate::toVar(){
	string out("");
	out += this->func + "_" + this->column;	
	return out;
}


bool Aggregate::equals(string aggr){
	return this->toString().compare(aggr) == 0;
}

bool Aggregate::isAggregate(string aggr){
	return count((char*)aggr.c_str(),"_") > 0;
}