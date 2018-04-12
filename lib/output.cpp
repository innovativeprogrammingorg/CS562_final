#include "output.h"

using namespace std;

string create_structures(vector<string>* select_attribute,vector<Column*>* columns){
	string out("struct mf_structure {\n");
	for(int i = 0;i<select_attribute->length();i++){
		string type;
		string name = select_attribute->at(i);
		for(int j = 0;j<columns->length();j++){
			if(name.find(columns->at(j)->name)!=string::npos){
				type = Value::getCppType(columns->at(j)->type);
			}
		}
		out += type + " " + name +";\n";
	}
	out += "};\n";
	out += "struct sales{\n";
	for(int i = 0;i<columns->length();i++){
		out += Value::getCppType(columns->at(i)) + " ";
		out += columns->at(i)->name + ";\n";
	}
	out += "};\n";
	return out;
}


vector<Column*>* getColumns(){
	SQLConn* conn = new SQLConn("information_schema");
	sql::ResultSet* res = conn->fetch(COLUMN_TYPE_QUERY);
	vector<Column*>* columns = new vector<Column*>();
	while(res->next()){
		columns->insert(new Column(res->getString("COLUMN_NAME"),res->getString("DATA_TYPE")));
	}
	delete conn;
	delete res;
	return columns;
}

vector<Aggregate*>* getAllAggregates(vector<string>* f_vect){
	vector<Aggregate*>* out = new vector<Aggregate*>();
	for(vector<string>::iterator it = f_vect->begin();it != f_vect->end();it++){
		out->insert(new Aggregate(*it));
	}
	return out;
}

vector<Aggregate*>* getSelectAggregates(vector<string>* select_attribute,vector<string>** select_columns){
	vector<Aggregate*>* out = new vector<Aggregate*>();
	
	for(vector<string>::iterator it = select_attribute->begin();it!= select_attribute->end();it++){
		if(Aggregate::isAggregate(*it)){
			out->insert(new Aggregate(*it));
		}else if(*select_columns != nullptr){
			(*select_columns)->insert(*it);
		}
	}
	return out;
}
/**
 * TODO make this strip them all!
 * @param  str [description]
 * @return     [description]
 */
string strip_grouping(string str){
	size_t index = str.find('.');
	if(index == string::npos){
		return str;
	}
	return str.substr(index+1);
}

string construct_initial_query(int group,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,vector<string>* grouping_attr,string select_cond){
	string out = "SELECT ";
	bool first = true;
	for(vector<string>::iterator it = select_columns->begin();it != select_columns->end();it++){
		if(first){
			out.append(*it);
			first = false;
		}else{
			out += ", ";
			out.append(*it);
		}
	}

	for(vector<Aggregate*>::iterator it = select_aggregates->begin();it != select_aggregates->end();it++){
		if((*it)->group != group){
			continue;
		}
		if(first){
			out.append((*it)->toSQL());
			first = false;
		}else{
			out += ", ";
			out.append((*it)->toSQL());
		}
	}
	out += " WHERE "+ strip_grouping(select_cond);
	out += " GROUP BY ";
	first = true;
	for(vector<string>::iterator it = select_columns->begin();it != select_columns->end();it++){
		if(first){
			out.append(*it);
			first = false;
		}else{
			out += ", ";
			out.append(*it);
		}
	}

	return out;
}

void parse_query(vector<string>* select_attribute,int no_grouping_vars,
				 vector<string>* grouping_attr,vector<string>* f_vect,vector<string>* select_cond_vect,string having){
	
	string header = OUTPUT_FILE_HEADER_START;

	vector<Column*>* columns =  getColumns();

	vector<Aggregate*>* all_aggregates = getAllAggregates(f_vect);
	vector<string>* select_columns = new vector<string>();
	vector<Aggregate*>* select_aggregates = getSelectAggregates(select_attribute,&select_columns);
		

	//Define the structures in the header
	header += create_mf_structure(select_attribute,columns);
	header += create_data_structure(columns);
	header += OUTPUT_FILE_HEADER_END;
	//Header is now finished
	string program = 
		"#include \"result.h\"\n"
		"using namespace std;\n"
		"int main(){\n"
		"\tsql:ResultSet* res;\n"
		"\tvector<struct mf_structure*>* mf_struct = new vector<struct mf_structure*>();\n";
	program += "\tSQLConn conn = new SQLConn(\""+DATABASE + "\");\n";
	for(int i = 0;i<=no_grouping_vars;i++){
		program.append("\tvector<struct sales*>* data");
		program.append(itoa(i));
		program.append(" = new vector<struct sales*>();\n");
		string scv = (i==0)? "" : select_cond_vect->at(i-1);
		program += "\tres = conn->fetch(\""+construct_initial_query(i,select_columns,select_aggregates,grouping_attr,svc) + "\");\n"
			"\twhile(res->next()){\n"
				"struct sales* entry "


	}

	


}