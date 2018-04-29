#include "query_parser.h"

using namespace std;

string Query_Parser::KEYWORDS[] = {
	"select",
	"from",
	"where",
	"group by",
	"such that",
	"having"
};

string Query_Parser::PARTS[] = {
	"SELECT ATTRIBUTE(S):",
	"WHERE(W):",
	"NUMBER OF GROUPING VARIABLES(n):",
	"GROUPING ATTRIBUTES(V):",
	"F-VECT([F]):",
	"SELECT CONDITION-VECT([σ]):",
	"HAVING_CONDITION(G):"
};
Query_Parser::Query_Parser(){
	string s;
	string v;
	string f;
	string n;

	cout<< Query_Parser::KEYWORDS[0] <<endl;
	getline(cin,s);
	cout << Query_Parser::KEYWORDS[1] << endl;
	getline(cin,this->where);
	cout<< Query_Parser::KEYWORDS[2] <<endl;
	getline(cin,n);
	this->no_grouping_vars = stoi(n);
	cout<< Query_Parser::KEYWORDS[3] <<endl;
	getline(cin,v);
	cout<< Query_Parser::KEYWORDS[4] <<endl;
	getline(cin,f);
	this->select_cond_vect = new vector<string>();
	cout<< Query_Parser::KEYWORDS[5] <<endl;
	char buffer[500];
	for(int i = 0;i<no_grouping_vars;i++){
		cout<<"SELECT CONDITION FOR "<<i+1<<endl;
		cin.getline(buffer,500);
		this->select_cond_vect->push_back(string(buffer));
	}
	cout<< Query_Parser::KEYWORDS[6] <<endl;
	getline(cin,this->having);

	this->select_attribute = explode(", ",s);
	this->grouping_attr = explode(", ",v);
	this->f_vect = explode(", ",f);
}

Query_Parser::Query_Parser(string file){
	string data = read_from_file(file);
	//cout<<"File contents:"<<endl<<data<<endl;
	string select;
	string from;
	string where;
	string group_by;
	string such_that;
	string having;
	vector<int> index;
	index.push_back(data.find(Query_Parser::KEYWORDS[0]));
	index.push_back(data.find(Query_Parser::KEYWORDS[1]));
	index.push_back(data.find(Query_Parser::KEYWORDS[2]));
	index.push_back(data.find(Query_Parser::KEYWORDS[3]));
	index.push_back(data.find(Query_Parser::KEYWORDS[4]));
	index.push_back(data.find(Query_Parser::KEYWORDS[5]));
	
	/**
	 * Process SELECT
	 */
	select = data.substr(index[0]+Query_Parser::KEYWORDS[0].length()+1,index[1] - (index[0]+Query_Parser::KEYWORDS[0].length() + 2));
	this->parse_select(select);
	/**Process FROM**/

	
}

	
void Query_Parser::parse_select(string select){

}

void Query_Parser::parse_group_by(string group_by){

}

void Query_Parser::parse_such_that(string such_that){

}

void Query_Parser::parse_f_vect(string query){

}