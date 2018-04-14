#include "debug.h"
using namespace std;



void print_vector(vector<string>* vec){
	int counter = 0;
	for(vector<string>::iterator it = vec->begin();it!=vec->end();it++){
		cout<<"["<<counter<<"]:"<<*it<<endl;
		counter++;
	}
}