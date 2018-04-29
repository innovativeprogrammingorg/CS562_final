#include "result.h"
using namespace std;

int vfind0(vector<struct group0*>* data , string prod, int64_t month){
	 size_t index = 0;
	for(vector<struct group0*>::iterator it = data->begin(); it != data->end(); it++){
		if(prod.compare((*it)->prod) == 0 && month == (*it)->month){
			return index;
		}
		index++;
	}
	 return -1;
}
int vfind1(vector<struct group1*>* data , string prod, int64_t month){
	 size_t index = 0;
	for(vector<struct group1*>::iterator it = data->begin(); it != data->end(); it++){
		if(prod.compare((*it)->prod) == 0 && month == (*it)->month){
			return index;
		}
		index++;
	}
	 return -1;
}
int vfind2(vector<struct group2*>* data , string prod, int64_t month){
	 size_t index = 0;
	for(vector<struct group2*>::iterator it = data->begin(); it != data->end(); it++){
		if(prod.compare((*it)->prod) == 0 && month == (*it)->month){
			return index;
		}
		index++;
	}
	 return -1;
}
bool is_unique(vector<struct sales*>* data,struct sales* entry){
	for(vector<struct sales*>::iterator it = data->begin();it != data->end();it++){
		if(entry->prod.compare((*it)->prod) == 0 && entry->month == (*it)->month){
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
	cout<<"|prod|month|1_avg_quant|2_avg_quant|"<<endl;
	for(auto it = mf_struct->begin(); it != mf_struct->end(); it++){
		cout<<"|"<<(*it)->prod<<"|"<<(*it)->month<<"|"<<(*it)->avg_quant_1<<"|"<<(*it)->avg_quant_2<<"|"<<endl;
	}
}
int main(){
	sql::ResultSet* res;
	vector<struct mf_structure*>* mf_struct = new vector<struct mf_structure*>();
	SQLConn* conn = new SQLConn("CS562");
	res = conn->fetch("SELECT * FROM test WHERE year = 1997");
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
	vector<struct group1*>* data1 = new vector<struct group1*>();
	vector<struct group2*>* data2 = new vector<struct group2*>();
	for(vector<struct sales*>::iterator it = uniques->begin();it != uniques->end();it++){
		struct mf_structure* entry = (struct mf_structure*)calloc(1,sizeof(struct mf_structure));
		entry->prod = (*it)->prod;
		entry->month = (*it)->month;
		mf_struct->push_back(entry);
		struct group0* entry0 = (struct group0*)calloc(1,sizeof(struct group0));
		entry0->prod = (*it)->prod;
		entry0->month = (*it)->month;
		data0->push_back(entry0);
		struct group1* entry1 = (struct group1*)calloc(1,sizeof(struct group1));
		entry1->prod = (*it)->prod;
		entry1->month = (*it)->month;
		data1->push_back(entry1);
		struct group2* entry2 = (struct group2*)calloc(1,sizeof(struct group2));
		entry2->prod = (*it)->prod;
		entry2->month = (*it)->month;
		data2->push_back(entry2);
	}
	for(auto it = uniques->begin();it != uniques->end();it++)
	for(auto xt = data->begin(); xt != data->end();xt++){
		size_t pos;
		if(true){
			pos = vfind0(data0,(*it)->prod,(*it)->month);
		}
	}
	for(auto it = uniques->begin();it != uniques->end();it++)
	for(auto xt = data->begin(); xt != data->end();xt++){
		size_t pos;
		if((*it)->prod == (*xt)->prod and (*it)->month < (*xt)->month){
			pos = vfind1(data1,(*it)->prod,(*it)->month);
			data1->at(pos)->avg_quant.add((*xt)->quant);
		}
	}
	for(auto it = uniques->begin();it != uniques->end();it++)
	for(auto xt = data->begin(); xt != data->end();xt++){
		size_t pos;
		if((*it)->prod == (*xt)->prod and (*it)->month > (*xt)->month){
			pos = vfind2(data2,(*it)->prod,(*it)->month);
			data2->at(pos)->avg_quant.add((*xt)->quant);
		}
	}
	for(auto it = mf_struct->begin();it != mf_struct->end(); it++){
		int pos0 = vfind0(data0,(*it)->prod,(*it)->month);
		int pos1 = vfind1(data1,(*it)->prod,(*it)->month);
		int pos2 = vfind2(data2,(*it)->prod,(*it)->month);
		if(!(true)){
			mf_struct->erase(it);
			it--;
			continue;
		}
		if(pos1 != -1){
			(*it)->avg_quant_1 = data1->at(pos1)->avg_quant.value();
		}else{
			mf_struct->erase(it);
			it--;
			continue;
		}
		if(pos2 != -1){
			(*it)->avg_quant_2 = data2->at(pos2)->avg_quant.value();
		}else{
			mf_struct->erase(it);
			it--;
			continue;
		}
	}
	print_mf_structure(mf_struct);
	return 0;
}
