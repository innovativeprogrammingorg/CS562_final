#ifndef _CONDITION_H_ 
#define _CONDITION_H_

#include <vector>
#include <string>
#include "../config.h"
#include "aggregate.h"
#include "../str.h"

using namespace std;

class Condition{
	public:
		int group;
		string column;
		string exp;
		string value;

		Condition(string cond);
		string toCpp(string var,vector<string>* select_columns);
};

#endif
