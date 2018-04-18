#include "result.h"
using namespace std;

size_t vfind1(vector<struct group1*>* data , string cust){
	 size_t index = 0;
	for(vector<struct group1*>::iterator it = data->begin(); it != data->end(); it++){
		if(cust == (*it)->cust){
			return index;
		}
		index++;
	}
	 return -1;
}
size_t vfind2(vector<struct group2*>* data , string cust){
	 size_t index = 0;
	for(vector<struct group2*>::iterator it = data->begin(); it != data->end(); it++){
		if(cust == (*it)->cust){
			return index;
		}
		index++;
	}
	 return -1;
}
size_t vfind3(vector<struct group3*>* data , string cust){
	 size_t index = 0;
	for(vector<struct group3*>::iterator it = data->begin(); it != data->end(); it++){
		if(cust == (*it)->cust){
			return index;
		}
		index++;
	}
	 return -1;
}
bool is_unique(vector<struct sales*>* data,struct sales* entry){
	for(vector<struct sales*>::iterator it = data->begin();it != data->end();it++){
		if(entry->cust == (*it)->cust){
			return false;
		}
	}
	return true;
}
vector<struct sales*>* get_uniques(vector<struct sales*>* data){
	vector<struct sales*>* out = new vector<struct sales*>();
	for(vector<struct sales*>::iterator it = data->begin();it != data->end();it++){
		if(is_unique(out,*it)){
			out->push_back(*it);
		}
	}
	return out;
}
int main(){
	sql::ResultSet* res;
	vector<struct mf_structure*>* mf_struct = new vector<struct mf_structure*>();
	SQLConn* conn = new SQLConn("CS562");
	res = conn->fetch("SELECT * FROM sales");
	vector<struct sales*>* data = new vector<struct sales*>();
	while(res->next()){
		struct sales* entry = (struct sales*)calloc(1,sizeof(struct sales));
		entry->cust = res->getString("cust");
		entry->prod = res->getString("prod");
		entry->day = res->getInt("day");
		entry->month = res->getInt("month");
		entry->year = res->getInt("year");
		entry->state = res->getString("state");
		entry->quant = res->getInt("quant");
		data->push_back(entry);
	}
	delete res;
	return 0;
}
