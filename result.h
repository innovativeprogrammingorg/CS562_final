#ifndef _RESULT_H_
#define _RESULT_H_ 
#include <string>
#include <vector>
#include <cstdint>
#include "lib/objects/sql.h"
struct mf_structure {
	string cust;
	int64_t sum_quant;
	int64_t sum_quant;
	int64_t sum_quant;
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
	int64_t sum_quant;
	int64_t avg_quant;
};
struct group3{
	string cust;
	int64_t sum_quant;
};
struct group3{
	string cust;
	int64_t sum_quant;
	int64_t avg_quant;
};
#endif