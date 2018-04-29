#include "query.h"

using namespace std;


string get_sql_res_function(int type){
	switch(type){
		case CPP_DATE:
		case CPP_STRING:
			return "getString";
		case CPP_INT64:
			return "getInt";
		case CPP_FLOAT:
			return "getFloat";
		case CPP_DOUBLE:
			return "getDouble";
		default:
			return "getString";
	}
}


string data_retrieval(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<string>* select_cond_vect,
					  vector<Aggregate*>* all_aggregates,vector<string>* grouping_attr,string where){
	string out("");
	out += "\tSQLConn* conn = new SQLConn(\"";
	out.append(DATABASE);
	out += "\");\n";
	out += "\tres = conn->fetch(\"SELECT * FROM ";
	out.append(TABLE);
	out += " WHERE "+where;
	out += "\");\n";
	out += "\tvector<struct sales*>* data = new vector<struct sales*>();\n"
		   "\twhile(res->next()){\n"
				"\t\tstruct sales* entry = (struct sales*)calloc(1,sizeof(struct sales));\n";
	for(vector<Column*>::iterator it = columns->begin();it!=columns->end();it++){
		out += "\t\tentry->"+(*it)->name + " = res->"+get_sql_res_function((*it)->ctype)+"(\""+(*it)->name+"\");\n";
	}
	out += "\t\tdata->push_back(entry);\n"
			"\t}\n"
			"\tdelete res;\n";

	return out;
}