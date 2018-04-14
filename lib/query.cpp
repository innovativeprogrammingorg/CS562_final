#include "query.h"

using namespace std;


string strip_grouping(string str){
	string out = str;
	size_t index;
	while((index = out.find('.'))!= string::npos){
		if(index < 3){
			out = out.substr(index+1);
		}else{
			out = out.substr(0,index-2) + out.substr(index+1);
		}
	}
	
	return out;
}

string construct_initial_query(int group,vector<string>* select_columns,vector<Aggregate*>* all_aggregates,vector<string>* grouping_attr,string select_cond){
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

	for(vector<Aggregate*>::iterator it = all_aggregates->begin();it != all_aggregates->end();it++){
		if((*it)->group != group){
			continue;
		}
		if(first){
			first = false;
		}else{
			out += ", ";
		}
		out.append((*it)->toSQL());
		out += " AS "+(*it)->toVar();
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
					  vector<Aggregate*>* all_aggregates,vector<string>* grouping_attr){
	string out("");
	out += "\tSQLConn conn = new SQLConn(\"";
	out.append(DATABASE);
	out += "\");\n";
	out += "\tres = conn->fetch(\"SELECT * FROM ";
	out.append(TABLE);
	out += "\");\n";
	out += "\tvector<struct sales*>* data = new vector<struct sales*>();\n"
		   "\twhile(res->next()){\n"
				"\t\tstruct sales* entry = (struct sales*)calloc(1,sizeof(struct sales*));\n";
	for(vector<Column*>::iterator it = columns->begin();it!=columns->end();it++){
		out += "\t\tentry->"+(*it)->name + " = res->"+get_sql_res_function((*it)->ctype)+"(\""+(*it)->name+"\");\n";
	}
	out += "\t\tdata->push_back(entry);\n"
			"\t}\n"
			"\t delete res;\n";

	for(int i = 1;i<=no_grouping_vars;i++){
		string datatype = "struct group"+itoa(i)+"*";
		out += "\tvector<"+datatype+">* data";
		out.append(itoa(i));
		out += " = new vector<"+datatype+">();\n";

		string scv = (i==0)? "" : select_cond_vect->at(i-1);

		out += "\tres = conn->fetch(\""+construct_initial_query(i,select_columns,all_aggregates,grouping_attr,scv) + "\");\n"
			   "\twhile(res->next()){\n";
	    
	    out += "\t\t" + datatype + " entry = ("+datatype+")calloc(1,sizeof("+datatype+"));\n";

	    for(vector<string>::iterator it = select_columns->begin();it!=select_columns->end();it++){
			string name = *it;
			int type;
			for(vector<Column*>::iterator jt = columns->begin();jt!=columns->end();jt++){
				if(name.compare((*jt)->name) == 0){
					type = (*jt)->ctype;
					break;
				}
			}
			out += "\t\tentry->"+name+ " = res->"+get_sql_res_function(type)+"(\""+name+"\");\n";
		}

	   	for(vector<Aggregate*>::iterator it = all_aggregates->begin();it!=all_aggregates->end();it++){
			if((*it)->group != i){
				continue;
			}
			string name = (*it)->column;
			int type;
			for(vector<Column*>::iterator jt = columns->begin();jt!=columns->end();jt++){
				if(name.find((*jt)->name) != string::npos){
					type = (*jt)->ctype;
					break;
				}
			}
			out += "\t\tentry->"+(*it)->toVar()+ " = res->"+get_sql_res_function(type)+"(\""+(*it)->toVar()+"\");\n";
		}
		out += "\t\tdata"+itoa(i)+"->push_back(entry);\n"
				"\t};\n";
		out += "\tdelete res;\n";
	}

	return out;
}