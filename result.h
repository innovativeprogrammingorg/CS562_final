#ifndef _RESULT_H_
#define _RESULT_H_ 
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <cppconn/resultset.h>
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
struct group1{
	string cust;
	int64_t sum_quant;
	int64_t avg_quant;
};
struct group2{
	string cust;
	int64_t sum_quant;
};
struct group3{
	string cust;
	int64_t sum_quant;
	int64_t avg_quant;
};
struct avg1quant{
	int count;
	int64_t sum;
};
struct avg3quant{
	int count;
	int64_t sum;
};
struct key{
};
struct keyComp {
	bool operator()(const std::string& a, const std::string& b) const {
		return a.compare(b) == 0;
	}
};
#endif