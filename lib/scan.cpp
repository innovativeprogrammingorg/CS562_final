#include "scan.h"

using namespace std;


vector<struct ct>* get_ct(vector<string>* select_columns, vector<Column*>* columns){
	vector<struct ct>* cols = new vector<struct ct>();
	for(vector<string>::iterator it = select_columns->begin();it!=select_columns->end();it++){
		struct ct c;
		c.name = *it;
		for(vector<Column*>::iterator jt = columns->begin();jt!=columns->end();jt++){
			if(c.name.find((*jt)->name)!=string::npos){
				c.type = (*jt)->type;
				break;
			}
		}
		cols->push_back(c);
	}
	return cols;
}

string get_helpers(int no_grouping_vars, vector<string>* select_columns, vector<Column*>* columns){
	vector<struct ct>* cols = get_ct(select_columns,columns);
	string out;
	bool first = true;


	for(int i = 1;i <= no_grouping_vars;i++){
		out += "int vfind"+ itoa(i) +"(vector<struct group"+itoa(i)+"*>* data ";
		string vfind_arg;
		string vfind_comp;
		bool first = true;
		for(vector<struct ct>::iterator it = cols->begin(); it != cols->end(); it++){
			vfind_arg = ", " + Column::getOutCppType(it->type) + " " + it->name;
			if(first){
				first = false;
			}else{
				vfind_comp += " && ";
			}
			switch(it->type){
				case CPP_STRING:
					vfind_comp += it->name +".compare((*it)->"+ it->name +") == 0";
					break;
				case CPP_INT64:
				case CPP_FLOAT:
				case CPP_DOUBLE:
					vfind_comp += it->name + " == " + "(*it)->" + it->name;
					break;
				case CPP_DATE:
				case CPP_RAW:
				case CPP_VECTOR:
					throw "Date, Raw, and Vector C++ types are not supported!";
					break;
			}
		}
		out += vfind_arg + "){\n"
			"\t size_t index = 0;\n"
			"\tfor(vector<struct group"+itoa(i)+"*>::iterator it = data->begin(); it != data->end(); it++){\n";
		out +=  "\t\tif("+vfind_comp+"){\n";
		out +=		"\t\t\treturn index;\n"
			    "\t\t}\n"
			    "\t\tindex++;\n"
			"\t}\n"
			"\t return -1;\n"
			"}\n";
	}
	
	out += "bool is_unique(vector<struct sales*>* data,struct sales* entry){\n"
		"\tfor(vector<struct sales*>::iterator it = data->begin();it != data->end();it++){\n";
	
	out += "\t\tif(";
	for(vector<struct ct>::iterator it = cols->begin();it != cols->end(); it++){
		if(first){
			first = false;
		}else{
			out += " && "; 
		}
		switch(it->type){
			case CPP_STRING:
				out += "entry->"+ it->name +".compare((*it)->"+ it->name +") == 0";
				break;
			case CPP_INT64:
			case CPP_FLOAT:
			case CPP_DOUBLE:
				out += "entry->"+ it->name + " == " + "(*it)->" + it->name;
				break;
			case CPP_DATE:
			case CPP_RAW:
			case CPP_VECTOR:
				throw "Date, Raw, and Vector C++ types are not supported!";
				break;
		}
	}
	out += "){\n"
			"\t\t\treturn false;\n"
		"\t\t}\n"
		"\t}\n"
		"\treturn true;\n"
		"}\n"
	    "vector<struct sales*>* get_uniques(vector<struct sales*>* data){\n"
			"\tvector<struct sales*>* out = new vector<struct sales*>();\n"
			"\tfor(vector<struct sales*>::iterator it = data->begin();it != data->end();it++){\n"
				"\t\tif(is_unique(out,*it)){\n"
					"\t\t\tout->push_back(*it);\n"
				"\t\t}\n"
			"\t}\n"
			"\treturn out;\n"
		"}\n";
	return out;
}

bool isColumn(string col,vector<Column*>* columns){
	for(auto it = columns->begin(); it != columns->end();it++){
		if(col.compare((*it)->name) == 0){
			return true;
		}
	}
	return false;
}

string parse_having(string having,vector<Column*>* columns){
	if(having.length()<1){
		return "false";
	}
	vector<string>* expl = c_explode(' ',having);
	string out;
	bool first = true;
	for(auto it = expl->begin(); it != expl->end(); it++){
		if(first){
			first = false;
		}else{
			out += " ";
		}
		if(Aggregate::isAggregate(*it)){
			Aggregate* tmp = new Aggregate(*it);
			out += "data" + itoa(tmp->group) + "->at(pos"+itoa(tmp->group)+")->"+tmp->toVar();
			delete tmp;
		}else if(isColumn(*it,columns)){
			out += "data->"+*it;
		}else{
			out += *it;
		}
	}
	return out;
}



string create_scans(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,
				    vector<Aggregate*>* all_aggregates,vector<Conditions*>* select_conditions,string having){
	//Initial scan to fill unique non-aggregates
	//variables
	string out = "\tvector<struct sales*>* uniques = get_uniques(data);\n";

	for(int i = 1;i<=no_grouping_vars;i++){
		out += "\tvector<struct group"+itoa(i)+"*>* data"+itoa(i)+ " = new vector<struct group"+itoa(i)+"*>();\n";
	}
	out +=  "\tfor(vector<struct sales*>::iterator it = uniques->begin();it != uniques->end();it++){\n"
				 "\t\tstruct mf_structure* entry = (struct mf_structure*)calloc(1,sizeof(struct mf_structure));\n";

	for(auto it = select_columns->begin(); it != select_columns->end(); it++){
		out += "\t\tentry->"+ *it + " = "+ "(*it)->" + *it + ";\n";
		out += "\t\tmf_struct->push_back(entry);\n";
	}

	for(int i = 1;i <= no_grouping_vars;i++){
		string type = "struct group"+itoa(i);
		string var = "entry"+itoa(i);
		out += "\t\t"+type + "* "+ var + " = (" + type + "*)calloc(1,sizeof("+type+"));\n";
		for(auto it = select_columns->begin(); it != select_columns->end(); it++){
			out += "\t\t"+ var +"->"+ *it + " = "+ "(*it)->" + *it + ";\n";
			out += "\t\tdata"+ itoa(i) +"->push_back("+ var +");\n";
		}
	}
	out += "\t}\n";
	//End initial scan
	//At this point, the mf_struct and the grouping variable tables are initialized with all the unique grouping id
	vector<struct ct>* cols = get_ct(select_columns,columns);
	
	
	//Scan part 2
	//TODO: Optimize THIS
	for(auto it = all_aggregates->begin(); it != all_aggregates->end(); it++){
		string type = "struct group"+itoa((*it)->group);
		string name = "data"+itoa((*it)->group);
		string field = (*it)->toVar();
		if((*it)->func.compare("avg") == 0 || (*it)->func.compare("AVG") == 0){
			string avg_type = "struct avg"+itoa((*it)->group)+(*it)->column;
			string avg_name = "tmp"+itoa((*it)->group)+(*it)->column;
			out += "\tauto "+avg_name + "= new map<struct key,"+avg_type+",keyComp>();\n";
			out += "\tfor(auto it = data->begin(); it != data->end(); it++){\n";
			out += "\t\tif(!("+select_conditions->at((*it)->group - 1)->toCpp("(*it)") + ")){\n";
			out += "\t\t\tcontinue;\n";
			out += "\t\t}\n";
			out += "\t\tstruct key search_key;\n";
			for(auto jt = select_columns->begin();jt != select_columns->end(); jt++){
				out += "\t\tsearch_key."+ *jt + " = (*it)->"+ *jt + ";\n";
			}
			out += "\t\tmap<struct key,"+avg_type+">::iterator pos;\n";
			out += "\t\tif((pos = "+avg_name+"->find(search_key)) == "+avg_name+"->end()){\n";
			out += "\t\t\t"+avg_type+" tmp_data;\n";
			out += "\t\t\ttmp_data.count = 1;\n";
			out += "\t\t\ttmp_data.sum = (*it)->"+(*it)->column+";\n";
			out += "\t\t\t"+avg_name +"->emplace(search_key,tmp_data);\n";
			out += "\t\t}else{\n"
				   "\t\t\tpos->second.count += 1;\n";
			out += "\t\t\tpos->second.sum += (*it)->"+(*it)->column+";\n";
			out += "\t\t}\n"
				   "\t}\n";
			out += "\tfor(auto it = "+avg_name+"->begin(); it != "+avg_name+"->end();it++){\n";
			out += "\t\tsize_t pos = vfind"+itoa((*it)->group)+"(data"+itoa((*it)->group);
			for(auto jt = select_columns->begin(); jt != select_columns->end(); jt++){
				out += ",it->first."+*jt;
			}
			out += ");\n";
			out += "\t\t"+name+"->at(pos)->"+field+" = " + "it->second.sum / it->second.count;\n";
			out += "\t}\n";
			out += "\tdelete "+avg_name+";\n";
		}else if((*it)->func.compare("sum") == 0 || (*it)->func.compare("SUM") == 0){
			out += "\tfor(auto it = data->begin(); it != data->end(); it++){\n";
			out += "\t\tif(!("+select_conditions->at((*it)->group - 1)->toCpp("(*it)") + ")){\n";
			out += "\t\t\tcontinue;\n";
			out += "\t\t}\n";
			out += "\t\tsize_t pos = vfind"+itoa((*it)->group)+"(data"+itoa((*it)->group);
			for(auto jt = select_columns->begin(); jt != select_columns->end(); jt++){
				out += ",(*it)->"+*jt;
			}
			out += ");\n";
			out += "\t\t"+name+"->at(pos)->"+field + " += (*it)->" + (*it)->column + ";\n";
			out += "\t}\n";
		}else if((*it)->func.compare("count") == 0 || (*it)->func.compare("COUNT") == 0){
			out += "\tfor(auto it = data->begin(); it != data->end(); it++){\n";
			out += "\t\tif(!("+select_conditions->at((*it)->group - 1)->toCpp("(*it)") + ")){\n";
			out += "\t\t\tcontinue;\n";
			out += "\t\t}\n";
			out += "\t\tsize_t pos = vfind"+itoa((*it)->group)+"(data"+itoa((*it)->group);
			for(auto jt = select_columns->begin(); jt != select_columns->end(); jt++){
				out += ",(*it)->"+*jt;
			}
			out += ");\n";
			out += "\t\t"+name+"->at(pos)->"+field + " += 1;\n";
			out += "\t}\n";
		}
	}
	//Scan Part 3
	out += "\tfor(auto it = mf_struct->begin();it != mf_struct->end(); it++){\n";
	string vfind_arg;
	for(auto jt = select_columns->begin(); jt != select_columns->end(); jt++){
		vfind_arg += ",(*it)->"+*jt;
	}
	for(int i = 1; i <= no_grouping_vars; i++){
		out += "\t\tint pos" + itoa(i) + " = vfind"+itoa(i)+"(data"+itoa(i)+vfind_arg+");\n";
	}
	out += "\t\tif(!("+parse_having(having,columns)+")){\n";
	out += "\t\t\tmf_struct->erase(it);\n"
		   "\t\t\tit--;"
		   "\t\t\tcontinue;\n"
	       "\t\t}\n";
	for(auto it = select_aggregates->begin();it != select_aggregates->end();it++){
		string group = itoa((*it)->group);
		
		out += "\t\tif(pos"+itoa((*it)->group)+" != -1){\n";
		out += "\t\t\t(*it)->"+(*it)->toABSVar() +" = data"+group+"->at(pos"+itoa((*it)->group)+")->"+(*it)->toVar()+";\n";
		out += "\t\t}else{\n";
		out += "\t\t\t(*it)->"+(*it)->toABSVar() +" = 0;\n";
		out += "\t\t}\n";
	}
	out += "\t}\n";
	
	return out;
}