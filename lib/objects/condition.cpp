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
	int index = strpos_m(tmp,4,string("="),string("<"),string(">"),string("!"));
	this->column = tmp.substr(0,index);
	if(index == -1){
		cout<<"Given the condition of "<<cond<<endl;
		throw "Error, invalid Condition";
	}else if( (index == strpos_m(tmp,4,string("<="),string(">="),string("!="),string("<>"))) != 0){
		this->exp = tmp.substr(index,2);
		if(this->exp.compare("<>") == 0){
			this->exp = "!=";
		}
		tmp = tmp.substr(index+2);
	}else{
		this->exp = tmp.substr(index,1);
		tmp = tmp.substr(index + 1);
	}
	this->value = str_replace("'","\"",tmp);
}


string Condition::toCpp(string var,string var2,vector<string>* select_columns,vector<Column*>* columns){
	string out; 
	if(Column::isColumn(this->value,columns)){
		string value = var2 + "->" + this->value;
		out = var + "->" +this->column;
		if(this->column.find("avg")!= string::npos){
			out+= ".value()";
		}
		if(this->value.find("\"") != string::npos){
			out += ".compare("+value+") == 0";
		}else if(this->exp.compare("=") != 0){
			out += " "+this->exp+" "+value;
		}else{
			out += " == " + value;
		}
	}else if(Aggregate::isAggregate(this->value)){
		Aggregate tmp = Aggregate(this->value);
		string vfind_arg;
		for(auto jt = select_columns->begin(); jt != select_columns->end(); jt++){
			vfind_arg += ","+var+"->"+*jt;
		}
		string pos = "vfind"+itoa(tmp.group)+"(data"+itoa(tmp.group)+vfind_arg+")";
		#if defined(NULL_EXPR_FALSE)
		out = "("+pos+" > 0 && ";
		#else 
		out = "("+pos+" == -1 || ";
		#endif
		string val = "data"+itoa(tmp.group)+"->at("+pos+")->"+tmp.toVar();
		out += var + "->" +this->column;

		if(this->column.find("avg") != string::npos){
			out+= ".value()";
		}
		if(this->value.find("avg") != string::npos){
			val += ".value()";
		}
		if(this->value.find("\"") != string::npos){
			out += ".compare("+val+") == 0";
		}else if(this->exp.compare("=") != 0){
			out += " "+this->exp+" "+val;
		}else{
			out += " == " + val;
		}
		out += ")";
	}else{
		out = var + "->" +this->column;
		if(this->column.find("avg")!= string::npos){
			out+= ".value()";
		}
		if(this->value.find("\"") != string::npos){
			out += ".compare("+this->value+") == 0";
		}else if(this->exp.compare("=") != 0){
			out += " "+this->exp+" "+this->value;
		}else{
			out += " == " + this->value;
		}
	}
	
	return out;
}
