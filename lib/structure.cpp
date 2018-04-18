#include "structures.h"

using namespace std;

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
	for(int i = 1;i<=no;i++){
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
			if((*it)->func.compare("avg") == 0 || (*it)->func.compare("AVG") == 0){
				avg_struct += "struct avg" + itoa((*it)->group) + (*it)->column + "{\n";
				
				avg_struct += "\tint count;\n";
				avg_struct += "\t"+type+" sum;\n";
				avg_struct += "};\n";
			}
			out += "\t"+type + " " + (*it)->toVar() +";\n";
		}
		out += "};\n";

	}
	out += avg_struct;

	out += "struct key{\n";
	out += key_groupers;
	out += "};\n";
	out += "struct keyComp {\n"
    "\tbool operator()(const std::string& a, const std::string& b) const {\n"
        "\t\treturn a.compare(b) == 0;\n"
    	"\t}\n"
	"};\n";

	return out;

}