#include "scan_generator.h"
using namespace std;



Scan_Generator::Scan_Generator(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,
				    vector<Aggregate*>* all_aggregates,vector<Conditions*>* select_conditions,string having){
	this->no_grouping_vars = no_grouping_vars;
	this->columns = columns;
	this->select_columns = select_columns;
	this->select_aggregates = select_aggregates;
	this->all_aggregates = all_aggregates;
	this->select_conditions = select_conditions;
	this->having = having;
}

string Scan_Generator::generate(){
	string out = this->prelim_scan();
	out += this->aggregate_scan();
	out += this->fill_mfstruct();
	return out;
}



string Scan_Generator::parse_having(){
	if(this->having.length()<1){
		return "true";
	}
	vector<string>* expl = c_explode(' ',this->having);
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
			if(tmp->func.compare("avg") == 0 || tmp->func.compare("AVG") == 0){
				out += ".value()";
			}
			delete tmp;
		}else if(Column::isColumn(*it,this->columns)){
			out += "data->"+*it;
		}else{
			out += *it;
		}
	}
	return out;
}

string Scan_Generator::get_selection_cond(int group){
	if(group == 0){
		return "\t\tif(true){\n";
	}
	return "\t\tif("+select_conditions->at(group - 1)->toCpp("(*it)",this->select_columns) + "){\n";
}

vector<vector<Aggregate*>> Scan_Generator::group_aggregates(){
	vector<vector<Aggregate*>> out;
	for(int i = 0; i <= this->no_grouping_vars; i++){
		out.push_back(vector<Aggregate*>());
	}
	for(auto it = this->all_aggregates->begin(); it != this->all_aggregates->end(); it++){
		out.at((*it)->group).push_back(*it);
	}
	return out;
}


string Scan_Generator::prelim_scan(){
	string out = "\tvector<struct sales*>* uniques = get_uniques(data);\n";

	for(int i = 0;i<=this->no_grouping_vars;i++){
		out += "\tvector<struct group"+itoa(i)+"*>* data"+itoa(i)+ " = new vector<struct group"+itoa(i)+"*>();\n";
	}
	out +=  "\tfor(vector<struct sales*>::iterator it = uniques->begin();it != uniques->end();it++){\n"
				 "\t\tstruct mf_structure* entry = (struct mf_structure*)calloc(1,sizeof(struct mf_structure));\n";

	for(auto it = this->select_columns->begin(); it != this->select_columns->end(); it++){
		out += "\t\tentry->"+ *it + " = "+ "(*it)->" + *it + ";\n";
		out += "\t\tmf_struct->push_back(entry);\n";
	}

	for(int i = 0;i <= this->no_grouping_vars;i++){
		string type = "struct group"+itoa(i);
		string var = "entry"+itoa(i);
		out += "\t\t"+type + "* "+ var + " = (" + type + "*)calloc(1,sizeof("+type+"));\n";
		for(auto it = this->select_columns->begin(); it != this->select_columns->end(); it++){
			out += "\t\t"+ var +"->"+ *it + " = "+ "(*it)->" + *it + ";\n";
			out += "\t\tdata"+ itoa(i) +"->push_back("+ var +");\n";
		}
	}
	out += "\t}\n";
	return out;
}


string Scan_Generator::aggregate_scan(){
	string out;
	vector<vector<Aggregate*>> groups = this->group_aggregates();
	for(auto xt = groups.begin(); xt !=  groups.end(); xt++){
		out += "\tfor(auto it = data->begin(); it != data->end();it++){\n";
		out += "\t\tsize_t pos;\n";
		for(auto it = xt->begin(); it != xt->end(); it++){
			string type = "struct group"+itoa((*it)->group);
			string name = "data"+itoa((*it)->group);
			string field = (*it)->toVar();
			if((*it)->func.compare("avg") == 0 || (*it)->func.compare("AVG") == 0){
				out += this->get_selection_cond((*it)->group);
				out += "\t\t\tpos = vfind"+itoa((*it)->group)+"("+name;
				for(auto jt = this->select_columns->begin(); jt != this->select_columns->end(); jt++){
					out += ",(*it)->"+*jt;
				}
				out += ");\n";
				out += "\t\t\t"+name+"->at(pos)->"+field + ".add((*it)->" + (*it)->column + ");\n";
				out += "\t\t}\n";
				
				
			}else if((*it)->func.compare("sum") == 0 || (*it)->func.compare("SUM") == 0){
				out += this->get_selection_cond((*it)->group);
			
				out += "\t\t\tpos = vfind"+itoa((*it)->group)+"("+name;
				for(auto jt = this->select_columns->begin(); jt != this->select_columns->end(); jt++){
					out += ",(*it)->"+*jt;
				}
				out += ");\n";
				out += "\t\t\t"+name+"->at(pos)->"+field + " += (*it)->" + (*it)->column + ";\n";
				out += "\t\t}\n";
			}else if((*it)->func.compare("count") == 0 || (*it)->func.compare("COUNT") == 0){
				out += this->get_selection_cond((*it)->group);
				
				out += "\t\t\tpos = vfind"+itoa((*it)->group)+"(data"+itoa((*it)->group);
				for(auto jt = this->select_columns->begin(); jt != this->select_columns->end(); jt++){
					out += ",(*it)->"+*jt;
				}
				out += ");\n";
				out += "\t\t\t"+name+"->at(pos)->"+field + " += 1;\n";
				out += "\t\t}\n";
			}else if((*it)->func.compare("min") == 0|| (*it)->func.compare("MIN") == 0){
				out += this->get_selection_cond((*it)->group);
				out += "\t\t\tpos = vfind"+itoa((*it)->group)+"(data"+itoa((*it)->group);
				for(auto jt = this->select_columns->begin(); jt != this->select_columns->end(); jt++){
					out += ",(*it)->"+*jt;
				}
				out += ");\n";
				out += "\t\t\tif("+name+"->at(pos)->"+field+"> (*it)->"+(*it)->column + "){\n";
				out += "\t\t\t\t"+name+"->at(pos)->"+field + " = (*it)->" +(*it)->column + ";\n";
				out += "\t\t\t}\n"; 
				out += "\t\t}\n";
			}else if((*it)->func.compare("max") == 0|| (*it)->func.compare("MAX") == 0){
				out += this->get_selection_cond((*it)->group);
				out += "\t\t\tpos = vfind"+itoa((*it)->group)+"(data"+itoa((*it)->group);
				for(auto jt = this->select_columns->begin(); jt != this->select_columns->end(); jt++){
					out += ",(*it)->"+*jt;
				}
				out += ");\n";
				out += "\t\t\tif("+name+"->at(pos)->"+field+"< (*it)->"+(*it)->column + "){\n";
				out += "\t\t\t\t"+name+"->at(pos)->"+field + " = (*it)->" +(*it)->column + ";\n";
				out += "\t\t\t}\n"; 
				out += "\t\t}\n";
			}
		}
		out += "\t}\n";
	}	
	return out;
}

string Scan_Generator::fill_mfstruct(){
	string out = "\tfor(auto it = mf_struct->begin();it != mf_struct->end(); it++){\n";
	string vfind_arg;
	for(auto jt = this->select_columns->begin(); jt != this->select_columns->end(); jt++){
		vfind_arg += ",(*it)->"+*jt;
	}
	cout<<"vfind_arg finished"<<endl;
	for(int i = 0; i <= this->no_grouping_vars; i++){
		out += "\t\tint pos" + itoa(i) + " = vfind"+itoa(i)+"(data"+itoa(i)+vfind_arg+");\n";
	}
	cout<<"pos vars finished"<<endl;
	out += "\t\tif(!("+this->parse_having()+")){\n";
	out += "\t\t\tmf_struct->erase(it);\n"
		   "\t\t\tit--;\n"
		   "\t\t\tcontinue;\n"
	       "\t\t}\n";
	for(auto it = this->select_aggregates->begin();it != this->select_aggregates->end();it++){
		string group = itoa((*it)->group);
		
		out += "\t\tif(pos"+itoa((*it)->group)+" != -1){\n";
		out += "\t\t\t(*it)->"+(*it)->toABSVar() +" = data"+group+"->at(pos"+itoa((*it)->group)+")->"+(*it)->toVar();
		if((*it)->func.compare("avg") == 0 || (*it)->func.compare("AVG") == 0){
			out += ".value()";
		}
		out += ";\n";
		out += "\t\t}else{\n";
		out += "\t\t\t(*it)->"+(*it)->toABSVar() +" = 0;\n";
		out += "\t\t}\n";
	}
	out += "\t}\n";
	return out;
}