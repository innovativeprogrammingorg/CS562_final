#include "structures.h"

using namespace std;

string create_structures(vector<string>* select_attribute,vector<Column*>* columns){
	string out("struct mf_structure {\n");
	for(vector<string>::iterator it = select_attribute->begin();it!=select_attribute->end();it++){
		string type;
		string name = *it;
		for(vector<Column*>::iterator jt = columns->begin();jt!=columns->end();jt++){
			if(name.find((*jt)->name)!=string::npos){
				type = Column::getOutCppType((*jt)->type);
				break;
			}
		}
		if(Aggregate::isAggregate(name)){
			Aggregate* tmp = new Aggregate(name);
			out += "\t"+type + " " + tmp->toVar() +";\n";
			delete tmp;
		}else{
			out += "\t"+type + " " + name +";\n";	
		}
		
	}
	out += "};\n";
	out += "struct sales{\n";
	for(vector<Column*>::iterator it = columns->begin();it!=columns->end();it++){
		out += "\t";
		out += Column::getOutCppType((*it)->type) + " ";
		out += (*it)->name + ";\n";
	}
	out += "};\n";
	return out;
}

string create_grouping_var_structs(int no,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* all_aggregates){
	string out("");

	for(int i = 1;i<=no;i++){
		out += "struct group"+itoa(no)+"{\n";
		for(vector<string>::iterator it = select_columns->begin();it!=select_columns->end();it++){
			string name = *it;
			string type;
			for(vector<Column*>::iterator jt = columns->begin();jt!=columns->end();jt++){
				if(name.compare((*jt)->name) == 0){
					type = Column::getOutCppType((*jt)->type);
					break;
				}
			}
			out += "\t"+type + " " + name +";\n";
		}
		for(vector<Aggregate*>::iterator it = all_aggregates->begin();it!=all_aggregates->end();it++){
			if((*it)->group != i){
				continue;
			}
			string name = (*it)->column;
			string type;
			for(vector<Column*>::iterator jt = columns->begin();jt!=columns->end();jt++){
				if(name.find((*jt)->name) != string::npos){
					type = Column::getOutCppType((*jt)->type);
					break;
				}
			}
			out += "\t"+type + " " + (*it)->toVar() +";\n";
		}
		out += "};\n";

	}

	return out;

}