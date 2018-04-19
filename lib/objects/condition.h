#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <vector>
#include <string>
#include "../str.h"

using namespace std;

class Condition{
	public:
		int group;
		string column;
		string exp;
		string value;

		Condition(string cond);
		string toCpp();
};

#endif