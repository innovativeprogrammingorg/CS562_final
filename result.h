#ifndef _RESULT_H_
#define _RESULT_H_ 
#include <string>
#include <vector>
#include <cstdint>
#include "lib/objects/sql.h"
struct mf_structure {
	string cust;
	int64_t sum_quant_1;
	int64_t sum_quant_2;
	int64_t sum_quant_3;
};
struct sales{
	string cust;
	string prod;
	int64_t day;
	int64_t month;
	int64_t year;
	string state;
	int64_t quant;
};
struct group3{
	string cust;
	int64_t sum_quant_1;
	int64_t avg_quant_1;
};
struct group3{
	string cust;
	int64_t sum_quant_2;
};
struct group3{
	string cust;
	int64_t sum_quant_3;
	int64_t avg_quant_3;
};
#endif