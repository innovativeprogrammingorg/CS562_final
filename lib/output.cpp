#include "output.h"

using namespace std;

string create_mf_structure(vector<string>* select_attribute,vector<Column*>* columns){
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
	return out;
}

void parse_query(vector<string>* select_attribute,int no_grouping_vars,
				 vector<string>* grouping_attr,vector<string>* f_vect,vector<string>* select_cond_vect,string having){
	string data("#include \"result.h\" \n using namespace std;\n");

	SQLConn* conn = new SQLConn("information_schema");

	sql::ResultSet* res = conn->fetch(COLUMN_TYPE_QUERY);
	vector<Column*>* columns = new vector<Column*>();
	while(res->next()){
		columns->insert(new Column(res->getString("COLUMN_NAME"),res->getString("DATA_TYPE")));
	}
	string mf_struct = create_mf_structure(select_attribute,columns);

}