#include "user.h"

using namespace std;

static string[] parts = {
	"SELECT ATTRIBUTE(S):",
	"NUMBER OF GROUPING VARIABLES(n):",
	"GROUPING ATTRIBUTES(V):",
	"F-VECT([F]):",
	"SELECT CONDITION-VECT([σ]):",
	"HAVING_CONDITION(G):"
};
void parse_user_input(){
	vector<string>* select_attribute;
	int no_grouping_vars;
	vector<string>* grouping_attr;
	vector<string>* f_vect;
	vector<string>* select_cond_vect;
	string having;

	string s;
	string v;
	string f;
	cout<< parts[0] <<endl;
	getline(cin,s);
	cout<< parts[1] <<endl;
	cin >> no_grouping_vars;
	cout<< parts[2] <<endl;
	getline(cin,v);
	cout<< parts[3] <<endl;
	getline(cin,f); 
	select_cond_vect = new vector<string>();
	cout<< parts[4] <<endl;
	char[500] buffer;
	for(int i = 0;i<no_grouping_vars;i++){
		cout<<"SELECT CONDITION FOR "<<i+1<<endl;
		cin.getline(buffer,500);
		select_cond_vect->insert(string(buffer));
	}
	cout<< parts[5] <<endl;
	getline(cin,having);

	select_attribute = explode(", ",s);
	grouping_attr = explode(", ",v);
	f_vect = explode(", ",f);

}

void parse_file_input(string file){
	vector<string>* select_attribute;
	int no_grouping_vars;
	vector<string>* grouping_attr;
	vector<string>* f_vect;
	vector<string>* select_cond_vect;
	string having;

	string data = read_from_file(file);

	
	string s;
	string v;
	string f;
	string svc;

	int64_t index1 = strpos(data,parts[0]);
	int64_t index2 = strpos(data,parts[1]);
	int64_t index3 = strpos(data,parts[2]);
	int64_t index4 = strpos(data,parts[3]);
	int64_t index5 = strpos(data,parts[4]);
	int64_t index6 = strpos(data,parts[5]);

	s = data.substr(index1+parts[0].length(),index2 - (index1+parts[0].length()));
	no_grouping_vars = atoi(trim(data.substr(index2+parts[1].length(),index3 - (index2+parts[1].length()))).c_str());
	v = data.substr(index3+parts[2].length(),index4 - (index3+parts[2].length()));
	f = data.substr(index4+parts[3].length(),index5 - (index4+parts[3].length()));
	svc = data.substr(index5+parts[4].length(),index6 - (index5+parts[4].length()));
	having = data.substr(index6+parts[5].length());

	select_attribute = explode(", ",s);
	grouping_attr = explode(", ",v);
	f_vect = explode(", ",f);
	select_cond_vect = explode("\n",svc);
}