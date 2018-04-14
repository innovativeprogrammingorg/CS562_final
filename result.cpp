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
		data->push_back(entry);
	}
	 delete res;
	vector<struct group1*>* data1 = new vector<struct group1*>();
	res = conn->fetch("SELECT cust, sum(quant) AS sum_quant, avg(quant) AS avg_quant WHERE state='NY' GROUP BY cust");
	while(res->next()){
		struct group1* entry = (struct group1*)calloc(1,sizeof(struct group1*));
		entry->cust = res->getString("cust");
		entry->sum_quant = res->getInt("sum_quant");
		entry->avg_quant = res->getInt("avg_quant");
		data1->push_back(entry);
	};
	delete res;
	vector<struct group2*>* data2 = new vector<struct group2*>();
	res = conn->fetch("SELECT cust, sum(quant) AS sum_quant WHERE state='NJ' GROUP BY cust");
	while(res->next()){
		struct group2* entry = (struct group2*)calloc(1,sizeof(struct group2*));
		entry->cust = res->getString("cust");
		entry->sum_quant = res->getInt("sum_quant");
		data2->push_back(entry);
	};
	delete res;
	vector<struct group3*>* data3 = new vector<struct group3*>();
	res = conn->fetch("SELECT cust, sum(quant) AS sum_quant, avg(quant) AS avg_quant WHERE state='CT' GROUP BY cust");
	while(res->next()){
		struct group3* entry = (struct group3*)calloc(1,sizeof(struct group3*));
		entry->cust = res->getString("cust");
		entry->sum_quant = res->getInt("sum_quant");
		entry->avg_quant = res->getInt("avg_quant");
		data3->push_back(entry);
	};
	delete res;
	return 0;
}
