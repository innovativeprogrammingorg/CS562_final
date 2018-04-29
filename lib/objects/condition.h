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

		/**
		 * Creates a new condition object from the condition string
		 */
		Condition(string cond);

		/**
		 * Converts this condition into a C++ expression which resolves to a bool
		 * @param  var            The variable which contains the column
		 * @param  var2           The variable which contains the value (May not be used)
		 * @param  grouping_atr   The grouping attributes
		 * @param  columns        The columns in the table
		 * @return                A bool expression
		 */
		string toCpp(string var,string var2,vector<string>* grouping_attr,vector<Column*>* columns);
};

#endif
