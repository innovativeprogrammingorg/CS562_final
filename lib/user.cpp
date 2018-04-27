#include "user.h"

using namespace std;

string parts[] = {
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
	string n;

	cout<< parts[0] <<endl;
	getline(cin,s);
	cout<< parts[1] <<endl;
	getline(cin,n);
	no_grouping_vars = stoi(n);
	cout<< parts[2] <<endl;
	getline(cin,v);
	cout<< parts[3] <<endl;
	getline(cin,f);
	select_cond_vect = new vector<string>();
	cout<< parts[4] <<endl;
	char buffer[500];
	for(int i = 0;i<no_grouping_vars;i++){
		cout<<"SELECT CONDITION FOR "<<i+1<<endl;
		cin.getline(buffer,500);
		select_cond_vect->push_back(string(buffer));
	}
	cout<< parts[5] <<endl;
	getline(cin,having);

	select_attribute = explode(", ",s);
	grouping_attr = explode(", ",v);
	f_vect = explode(", ",f);
	parse_query(select_attribute,no_grouping_vars,grouping_attr,f_vect,select_cond_vect,having);

}

void parse_file_input(string file){
	//cout<<"Parsing the file: "<<file<<endl;
	vector<string>* select_attribute;
	int no_grouping_vars;
	vector<string>* grouping_attr;
	vector<string>* f_vect;
	vector<string>* select_cond_vect;
	string having;

	string data = read_from_file(file);
	//cout<<"File contents:"<<endl<<data<<endl;
	
	string s;
	string v;
	string f;
	string svc;

	int64_t index1 = data.find(parts[0]);
	int64_t index2 = data.find(parts[1]);
	int64_t index3 = data.find(parts[2]);
	int64_t index4 = data.find(parts[3]);
	int64_t index5 = data.find(parts[4]);
	int64_t index6 = data.find(parts[5]);

	s = data.substr(index1+parts[0].length()+1,index2 - (index1+parts[0].length() + 2));
	cout<<"S: "<<s<<endl;
	no_grouping_vars = atoi(trim(data.substr(index2+parts[1].length(),index3 - (index2+parts[1].length()))).c_str());
	cout<<"No. of Grouping Variables: "<<no_grouping_vars<<endl;
	v = data.substr(index3+parts[2].length()+1,index4 - (index3+parts[2].length() + 2));
	cout<<"V: "<<v<<endl;
	f = data.substr(index4+parts[3].length()+1,index5 - (index4+parts[3].length() + 2));
	cout<<"F: "<<f<<endl;
	svc = data.substr(index5+parts[4].length()+1,index6 - (index5+parts[4].length() + 2));
	cout<<"SVC: "<<svc<<endl;
	having = data.substr(index6+parts[5].length()+1);
	cout<<"Having: "<<having<<endl;

	select_attribute = explode(", ",s);
	grouping_attr = explode(", ",v);
	f_vect = explode(", ",f);
	cout<<"++++++AFTER PARSING++++++++"<<endl;
	select_cond_vect = explode("\n",svc);
	cout<<parts[0]<<endl;
	print_vector(select_attribute);
	cout<<parts[2]<<endl;
	print_vector(grouping_attr);
	cout<<parts[3]<<endl;
	print_vector(f_vect);
	cout<<parts[4]<<endl;
	print_vector(select_cond_vect);
	parse_query(select_attribute,no_grouping_vars,grouping_attr,f_vect,select_cond_vect,having);
}