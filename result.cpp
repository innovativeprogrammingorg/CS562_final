#include "result.h"
using namespace std;
int main(){
	sql:ResultSet* res;
	vector<struct mf_structure*>* mf_struct = new vector<struct mf_structure*>();
	SQLConn conn = new SQLConn("CS562");
	res = conn->fetch("SELECT * FROM sales");
	vector<struct sales*>* data = new vector<struct sales*>();
	while(res->next()){
		struct sales* entry = (struct sales*)calloc(1,sizeof(struct sales*));
		entry->cust = res->getString("cust");
		entry->prod = res->getString("prod");
		entry->day = res->getInt("day");
		entry->month = res->getInt("month");
		entry->year = res->getInt("year");
		entry->state = res->getString("state");
		entry->quant = res->getInt("quant");
		data->insert(entry);
	}
	 delete res;
	vector<struct sales*>* data1 = new vector<struct group*>();
	res = conn->fetch("SELECT cust, sum(quant), avg(quant) WHERE state='NY' GROUP BY cust");
	while(res->next()){
		struct group1** entry = (struct group1*)calloc(1,sizeof(struct group1*));		entry->cust = res->getString("cust");
		entry->quant = res->getInt("quant");
		entry->quant = res->getInt("quant");
		data1->insert(entry);
	};
	vector<struct sales*>* data2 = new vector<struct group*>();
	res = conn->fetch("SELECT cust, sum(quant) WHERE state='NJ' GROUP BY cust");
	while(res->next()){
		struct group2** entry = (struct group2*)calloc(1,sizeof(struct group2*));		entry->cust = res->getString("cust");
		entry->quant = res->getInt("quant");
		data2->insert(entry);
	};
	vector<struct sales*>* data3 = new vector<struct group*>();
	res = conn->fetch("SELECT cust, sum(quant), avg(quant) WHERE state='CT' GROUP BY cust");
	while(res->next()){
		struct group3** entry = (struct group3*)calloc(1,sizeof(struct group3*));		entry->cust = res->getString("cust");
		entry->quant = res->getInt("quant");
		entry->quant = res->getInt("quant");
		data3->insert(entry);
	};
	return 0;
}
