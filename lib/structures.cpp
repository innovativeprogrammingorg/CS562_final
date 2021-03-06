#include "structures.h"

using namespace std;

string create_output_printer(vector<string>* select_attribute,vector<Column*>* columns){
	string out = "void print_mf_structure(vector<struct mf_structure*>* mf_struct){\n"
				 "\tcout<<\"|";
	for(auto it = select_attribute->begin();it!=select_attribute->end();it++){
		out += *it + "|";
	}
	out += "\"<<endl;\n"
		   "\tfor(auto it = mf_struct->begin(); it != mf_struct->end(); it++){\n"
		   "\t\tcout<<\"|\"";
	for(auto it = select_attribute->begin();it!=select_attribute->end();it++){
		out += "<<";
		string name = *it;
		if(Aggregate::isAggregate(name)){
			Aggregate* tmp = new Aggregate(name);
			out += "(*it)->"+tmp->toABSVar();
			delete tmp;
		}else{
			out += "(*it)->"+ name;	
		}
		out +="<<\"|\"";
	}
	out += "<<endl;\n"
		"\t}\n"
		"}\n";
	return out;
}

string create_structures(vector<string>* select_attribute,vector<Column*>* columns){
	string out("struct mf_structure {\n");
	for(auto it = select_attribute->begin();it!=select_attribute->end();it++){
		string type;
		string name = *it;
		for(auto jt = columns->begin();jt!=columns->end();jt++){
			if(name.find((*jt)->name)!=string::npos){
				type = Column::getOutCppType((*jt)->type);
				break;
			}
		}
		if(Aggregate::isAggregate(name)){
			Aggregate* tmp = new Aggregate(name);
			if(type.compare("string") == 0){
				type = "int64_t";
			}
			out += "\t"+type + " " + tmp->toABSVar() +";\n";

			delete tmp;
		}else{
			out += "\t"+type + " " + name +";\n";	
		}
		
	}
	out += "};\n";
	out += "struct sales{\n";
	for(auto it = columns->begin();it!=columns->end();it++){
		out += "\t";
		out += Column::getOutCppType((*it)->type) + " ";
		out += (*it)->name + ";\n";
	}
	out += "};\n";
	
	
	return out;
}

string create_grouping_var_structs(int no,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* all_aggregates){
	string out("");
	string avg_struct;
	string key_groupers = "";
	for(int i = 0;i<=no;i++){
		out += "struct group"+itoa(i)+"{\n";
		string groupers;
		for(auto it = select_columns->begin();it!=select_columns->end();it++){
			string name = *it;
			string type;
			for(auto jt = columns->begin();jt!=columns->end();jt++){
				if(name.compare((*jt)->name) == 0){
					type = Column::getOutCppType((*jt)->type);
					break;
				}
			}
			groupers += "\t"+type + " " + name +";\n";
		}
		out += groupers;
		key_groupers = groupers;
		for(auto it = all_aggregates->begin();it!=all_aggregates->end();it++){
			if((*it)->group != i){
				continue;
			}
			string name = (*it)->column;
			string type;
			for(auto jt = columns->begin();jt!=columns->end();jt++){
				if(name.find((*jt)->name) != string::npos){
					type = Column::getOutCppType((*jt)->type);
					break;
				}
			}
			if((*it)->func.compare("count") == 0){
				type = "int64_t";
			}
			if((*it)->func.compare("avg") == 0 || (*it)->func.compare("AVG") == 0){
				out += "\tAverage<"+type+"> " + (*it)->toVar() + ";\n";
			}else{
				out += "\t"+type + " " + (*it)->toVar() +";\n";
			}
		}
		out += "};\n";
	}
	return out;
}