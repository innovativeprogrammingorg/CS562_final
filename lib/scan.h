#ifndef _SCAN_H_
#define _SCAN_H_

#include <string>
#include <vector>
#include <map>
#include "objects/column.h"
#include "objects/aggregate.h"
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

string get_helpers(int no_grouping_vars, vector<string>* select_columns, vector<Column*>* columns);

#endif