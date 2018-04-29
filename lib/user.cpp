#include "user.h"

using namespace std;

string parts[] = {
	"SELECT ATTRIBUTE(S):",
	"WHERE(W):",
	"NUMBER OF GROUPING VARIABLES(n):",
	"GROUPING ATTRIBUTES(V):",
	"F-VECT([F]):",
	"SELECT CONDITION-VECT([σ]):",
	"HAVING_CONDITION(G):"
};

void parse_user_input(bool emf){
	vector<string>* select_attribute;
	int no_grouping_vars;
	vector<string>* grouping_attr;
	vector<string>* f_vect;
	vector<string>* select_cond_vect;
	string having;
	string where;

	string s;
	string v;
	string f;
	string n;

	cout<< parts[0] <<endl;
	getline(cin,s);
	cout << parts[1] << endl;
	getline(cin,where);
	cout<< parts[2] <<endl;
	getline(cin,n);
	no_grouping_vars = stoi(n);
	cout<< parts[3] <<endl;
	getline(cin,v);
	cout<< parts[4] <<endl;
	getline(cin,f);
	select_cond_vect = new vector<string>();
	cout<< parts[5] <<endl;
	char buffer[500];
	for(int i = 0;i<no_grouping_vars;i++){
		cout<<"SELECT CONDITION FOR "<<i+1<<endl;
		cin.getline(buffer,500);
		select_cond_vect->push_back(string(buffer));
	}
	cout<< parts[6] <<endl;
	getline(cin,having);

	select_attribute = explode(", ",s);
	grouping_attr = explode(", ",v);
	f_vect = explode(", ",f);
	parse_query(select_attribute,where,no_grouping_vars,grouping_attr,f_vect,select_cond_vect,having,emf);

}

void parse_file_input(string file,bool emf){
	//cout<<"Parsing the file: "<<file<<endl;
	vector<string>* select_attribute;
	int no_grouping_vars;
	vector<string>* grouping_attr;
	vector<string>* f_vect;
	vector<string>* select_cond_vect;
	string having;
	string where;
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
	int64_t index7 = data.find(parts[6]);

	s = data.substr(index1+parts[0].length()+1,index2 - (index1+parts[0].length() + 2));
	cout<<"S: "<<s<<endl;

	where = data.substr(index2+parts[1].length()+1,index3 - (index2+parts[1].length() + 2));
	cout<<"W:"<<where<<endl;

	no_grouping_vars = atoi(trim(data.substr(index3+parts[2].length(),index4 - (index3+parts[2].length()))).c_str());
	cout<<"No. of Grouping Variables: "<<no_grouping_vars<<endl;

	v = data.substr(index4+parts[3].length()+1,index5 - (index4+parts[3].length() + 2));
	cout<<"V: "<<v<<endl;

	f = data.substr(index5+parts[4].length()+1,index6 - (index5+parts[4].length() + 2));
	cout<<"F: "<<f<<endl;

	if(no_grouping_vars>0){
		svc = data.substr(index6+parts[5].length()+1,index7 - (index6+parts[5].length() + 2));
	}else{
		svc = "";
	}
	cout<<"SVC: "<<svc<<endl;
	
	having = data.substr(index7+parts[6].length()+1);
	cout<<"Having: "<<having<<endl;

	select_attribute = explode(", ",s);
	grouping_attr = explode(", ",v);
	f_vect = explode(", ",f);
	cout<<"++++++AFTER PARSING++++++++"<<endl;
	select_cond_vect = explode("\n",svc);
	cout<<parts[0]<<endl;
	print_vector(select_attribute);
	cout<<parts[3]<<endl;
	print_vector(grouping_attr);
	cout<<parts[4]<<endl;
	print_vector(f_vect);
	cout<<parts[5]<<endl;
	print_vector(select_cond_vect);
	parse_query(select_attribute,where,no_grouping_vars,grouping_attr,f_vect,select_cond_vect,having,emf);
}