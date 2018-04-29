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
		/**
		 * All of the conditions contained in this object
		 */
		vector<Condition*>* conditions;
		/**
		 * The operators, currently will support and, or, xor
		 * Other operators can be place in the condition itself
		 */
		vector<string>* ops;
		/**
		 * Creates a representation of a group of such that conditions
		 * Note that unlike the having clause, this is white space sensitive!
		 * Condition should be of the format
		 * X>Y and Y=Z
		 * Notice the spaces exist only between the expressions and the operator
		 */
		Conditions(string conds);
		/**
		 * Frees up the memory used by this object
		 */
		virtual ~Conditions();
		/**
		 * Converts all of this objects conditions into a single C++ expression which
		 * evaluates to bool
		 * @param  var            The variable for the first value ig y in y>x
		 * @param  var2           The variable for the second value. ig x in y>x 
		 * @param  select_columns The columns in the select statement
		 * @param  columns        The columns in the table
		 * @return                A bool expression
		 */
		string toCpp(string var,string var2,vector<string>* select_columns,vector<Column*>* columns);

		/**
		 * Processes the such that conditions
		 */
		static vector<Conditions*>* getConditions(vector<string>* cond);
};

#endif