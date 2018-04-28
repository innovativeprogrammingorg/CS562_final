#include "output.h"

using namespace std;

vector<Column*>* getColumns(){
	SQLConn* conn = new SQLConn("information_schema");
	string query = "SELECT * FROM `COLUMNS` WHERE `TABLE_NAME` = \'"+string(TABLE)+"\' AND `TABLE_SCHEMA` = \'"+string(DATABASE)+"\'";
	sql::ResultSet* res = conn->fetch(query);
	vector<Column*>* columns = new vector<Column*>();
	while(res->next()){
		columns->push_back(new Column(res->getString("COLUMN_NAME"),res->getString("DATA_TYPE")));
	}
	delete conn;
	delete res;
	return columns;
}

vector<Aggregate*>* getAllAggregates(vector<string>* f_vect){
	vector<Aggregate*>* out = new vector<Aggregate*>();
	for(vector<string>::iterator it = f_vect->begin();it != f_vect->end();it++){
		out->push_back(new Aggregate(*it));
	}
	return out;
}

vector<Aggregate*>* getSelectAggregates(vector<string>* select_attribute,vector<string>** select_columns){
	vector<Aggregate*>* out = new vector<Aggregate*>();
	
	for(vector<string>::iterator it = select_attribute->begin();it!= select_attribute->end();it++){
		if(Aggregate::isAggregate(*it)){
			out->push_back(new Aggregate(*it));
		}else if(*select_columns != nullptr){
			(*select_columns)->push_back(*it);
		}
	}
	return out;
}


void parse_query(vector<string>* select_attribute,int no_grouping_vars,
				 vector<string>* grouping_attr,vector<string>* f_vect,vector<string>* select_cond_vect,string having){
	
	string header = OUTPUT_FILE_HEADER_START;

	vector<Column*>* columns =  getColumns();
	//print_vector(columns);
	vector<Aggregate*>* all_aggregates = getAllAggregates(f_vect);
	vector<string>* select_columns = new vector<string>();
	vector<Aggregate*>* select_aggregates = getSelectAggregates(select_attribute,&select_columns);
	vector<Conditions*>* select_conditions = Conditions::getConditions(select_cond_vect);
	//Define the structures in the header
	header += create_structures(select_attribute,columns);
	header += create_grouping_var_structs(no_grouping_vars,columns,select_columns,all_aggregates);
	header += OUTPUT_FILE_HEADER_END;
	//Header is now finished
	string program = 
		"#include \"result.h\"\n"
		"using namespace std;\n\n";
	program += get_helpers(no_grouping_vars,grouping_attr,columns);
	program += create_output_printer(select_attribute,columns);

	program += "int main(){\n"
		"\tsql::ResultSet* res;\n"
		"\tvector<struct mf_structure*>* mf_struct = new vector<struct mf_structure*>();\n";

	program += data_retrieval(no_grouping_vars,columns,select_columns,select_cond_vect,all_aggregates,grouping_attr);
	Scan_Generator* gen = new Scan_Generator(no_grouping_vars,columns,select_columns,select_aggregates,all_aggregates,select_conditions,having,grouping_attr);
	program += gen->generate();
	program += "\tprint_mf_structure(mf_struct);\n";
	program += "\treturn 0;\n"
				"}\n";
	write_to_file("",OUTPUT_FILE_HEADER_LOCATION,header);
	write_to_file("",OUTPUT_FILE,program);

	delete columns;
	delete all_aggregates;
	delete select_columns;
	delete select_aggregates;
	delete gen;

}