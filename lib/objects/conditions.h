#ifndef _CONDITIONS_H_
#define _CONDITIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include "column.h"
#include "condition.h"


using namespace std;



class Conditions{
	public:
		vector<Condition*>* conditions;
		vector<string>* ops;

		Conditions(string conds);
		virtual ~Conditions();
		string toCpp(string var,vector<string>* select_columns);
		static vector<Conditions*>* getConditions(vector<string>* cond);
};

#endif