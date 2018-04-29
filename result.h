#ifndef _RESULT_H_
#define _RESULT_H_ 
#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <cppconn/resultset.h>
#include "lib/str.h"
#include "lib/objects/average.h"
#include "lib/objects/sql.h"
struct mf_structure {
	string prod;
	int64_t month;
	int64_t avg_quant_1;
	int64_t avg_quant_2;
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
struct group0{
	string prod;
	int64_t month;
};
struct group1{
	string prod;
	int64_t month;
	Average<int64_t> avg_quant;
};
struct group2{
	string prod;
	int64_t month;
	Average<int64_t> avg_quant;
};
#endif