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
	vector<struct sales*>* uniques = get_uniques(data);
	vector<struct group1*>* data1 = new vector<struct group1*>();
	vector<struct group2*>* data2 = new vector<struct group2*>();
	vector<struct group3*>* data3 = new vector<struct group3*>();
	for(vector<struct sales*>::iterator it = uniques->begin();it != uniques->end();it++){
		struct mf_structure* entry = (struct mf_structure*)calloc(1,sizeof(struct mf_structure));
		entry->cust = (*it)->cust;
		mf_struct->push_back(entry);
		struct group1* entry1 = (struct group1*)calloc(1,sizeof(struct group1));
		entry1->cust = (*it)->cust;
		data1->push_back(entry1);
		struct group2* entry2 = (struct group2*)calloc(1,sizeof(struct group2));
		entry2->cust = (*it)->cust;
		data2->push_back(entry2);
		struct group3* entry3 = (struct group3*)calloc(1,sizeof(struct group3));
		entry3->cust = (*it)->cust;
		data3->push_back(entry3);
	}
	for(auto it = data->begin(); it != data->end(); it++){
		size_t pos = vfind1(data1,it->first.cust);
		data1->at(pos)->sum_quant += (*it)->quant;
	}
	map<struct key,struct avg1quant>*tmp1quant= new map<struct key,struct avg1quant,keyComp>();
	for(auto it = data->begin(); it != data->end(); it++){
		struct key search_key;
		search_key.cust = (*it)->cust;
		map<struct key,struct avg1quant>::iterator pos;
		if((pos = tmp1quant->find(search_key)) == map::npos){
			struct avg1quant tmp_data;
			tmp_data.count = 1;
			tmp_data.sum = (*it)->quant;
			tmp1quant->emplace(search_key,tmp_data);
		}else{
			pos->count += 1;
			pos->sum += (*it)->quant;
		}
	}
	for(auto it = tmp1quant->begin(); it != tmp1quant->end();it++){
		size_t pos = vfind1(data1,it->first.cust);
		data1->at(pos)->avg_quant = it->second.sum / it->second.count;
	}
	for(auto it = data->begin(); it != data->end(); it++){
		size_t pos = vfind2(data2,it->first.cust);
		data2->at(pos)->sum_quant += (*it)->quant;
	}
	for(auto it = data->begin(); it != data->end(); it++){
		size_t pos = vfind3(data3,it->first.cust);
		data3->at(pos)->sum_quant += (*it)->quant;
	}
	map<struct key,struct avg3quant>*tmp3quant= new map<struct key,struct avg3quant,keyComp>();
	for(auto it = data->begin(); it != data->end(); it++){
		struct key search_key;
		search_key.cust = (*it)->cust;
		map<struct key,struct avg3quant>::iterator pos;
		if((pos = tmp3quant->find(search_key)) == map::npos){
			struct avg3quant tmp_data;
			tmp_data.count = 1;
			tmp_data.sum = (*it)->quant;
			tmp3quant->emplace(search_key,tmp_data);
		}else{
			pos->count += 1;
			pos->sum += (*it)->quant;
		}
	}
	for(auto it = tmp3quant->begin(); it != tmp3quant->end();it++){
		size_t pos = vfind3(data3,it->first.cust);
		data3->at(pos)->avg_quant = it->second.sum / it->second.count;
	}
	return 0;
}
