#include "result.h"
using namespace std;

int vfind0(vector<struct group0*>* data , string prod, string cust){
	 size_t index = 0;
	for(vector<struct group0*>::iterator it = data->begin(); it != data->end(); it++){
		if(prod.compare((*it)->prod) == 0 && cust.compare((*it)->cust) == 0){
			return index;
		}
		index++;
	}
	 return -1;
}
bool is_unique(vector<struct sales*>* data,struct sales* entry){
	for(vector<struct sales*>::iterator it = data->begin();it != data->end();it++){
		if(entry->prod.compare((*it)->prod) == 0 && entry->cust.compare((*it)->cust) == 0){
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
void print_mf_structure(vector<struct mf_structure*>* mf_struct){
	cout<<"|prod|cust|avg_quant|"<<endl;
	for(auto it = mf_struct->begin(); it != mf_struct->end(); it++){
		cout<<"|"<<(*it)->prod<<"|"<<(*it)->cust<<"|"<<(*it)->avg_quant<<"|"<<endl;
	}
}
int main(){
	sql::ResultSet* res;
	vector<struct mf_structure*>* mf_struct = new vector<struct mf_structure*>();
	SQLConn* conn = new SQLConn("CS562");
	res = conn->fetch("SELECT * FROM test");
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
	vector<struct sales*>* uniques = get_uniques(data);
	vector<struct group0*>* data0 = new vector<struct group0*>();
	for(vector<struct sales*>::iterator it = uniques->begin();it != uniques->end();it++){
		struct mf_structure* entry = (struct mf_structure*)calloc(1,sizeof(struct mf_structure));
		entry->prod = (*it)->prod;
		entry->cust = (*it)->cust;
		mf_struct->push_back(entry);
		struct group0* entry0 = (struct group0*)calloc(1,sizeof(struct group0));
		entry0->prod = (*it)->prod;
		entry0->cust = (*it)->cust;
		data0->push_back(entry0);
	}
	for(auto it = data->begin(); it != data->end();it++){
		size_t pos;
		if(true){
			pos = vfind0(data0,(*it)->prod,(*it)->cust);
			data0->at(pos)->avg_quant.add((*it)->quant);
		}
	}
	for(auto it = mf_struct->begin();it != mf_struct->end(); it++){
		int pos0 = vfind0(data0,(*it)->prod,(*it)->cust);
		if(!(true)){
			mf_struct->erase(it);
			it--;
			continue;
		}
		if(pos0 != -1){
			(*it)->avg_quant = data0->at(pos0)->avg_quant.value();
		}else{
			mf_struct->erase(it);
			it--;
			continue;
		}
	}
	print_mf_structure(mf_struct);
	return 0;
}
