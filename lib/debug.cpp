#include "debug.h"
using namespace std;



void print_vector(vector<string>* vec){
	if(vec == nullptr){
		cout<<"nullptr"<<endl;
		return;
	}
	int counter = 0;
	for(auto it = vec->begin();it!=vec->end();it++){
		cout<<"["<<counter<<"]:"<<*it<<endl;
		counter++;
	}
}

void print_vector(vector<Column*>* vec){
	if(vec == nullptr){
		cout<<"nullptr"<<endl;
		return;
	}
	int counter = 0;
	for(auto it = vec->begin();it!=vec->end();it++){
		cout<<"["<<counter<<"]:"<<"Name:"<<(*it)->name<<" Type:"<<(*it)->type<<" CType:"<<(*it)->ctype<<endl;
		counter++;
	}
}