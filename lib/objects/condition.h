#ifndef _CONDITION_H_ 
#define _CONDITION_H_

#include <iostream>
#include <vector>
#include <string>
#include "../config.h"
#include "aggregate.h"
#include "column.h"
#include "../str.h"

using namespace std;

class Condition{
	public:
		int group;
		string column;
		string exp;
		string value;

		Condition(string cond);
		string toCpp(string var,string var2,vector<string>* select_columns,vector<Column*>* columns);
};

#endif
