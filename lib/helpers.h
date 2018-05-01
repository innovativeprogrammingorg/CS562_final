#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <string>
#include <vector>
#include "objects/column.h"
#include "str.h"

using namespace std;
struct ct{
	string name;
	int type;
};


/**
 * Returns a vector of structs which contains the name and type of each column that is
 * going to be selected
 */
vector<struct ct>* get_ct(vector<string>* select_columns, vector<Column*>* columns);

/**
 * Creates helper functions for the final output program
 * @param  no_grouping_vars The number of grouping variables
 * @param  grouping_atr     The columns in the group by statement
 * @param  columns          The columns in the table
 * @return                  The helper functions for the program
 */
string get_helpers(int no_grouping_vars, vector<string>* grouping_atr, vector<Column*>* columns);



#endif