#ifndef _SCAN_H_
#define _SCAN_H_

#include <string>
#include <vector>
#include <map>
#include "objects/column.h"
#include "objects/aggregate.h"
#include "objects/conditions.h"
#include "str.h"
#include "debug.h"

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
string create_scans(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,
				    vector<Aggregate*>* all_aggregates,vector<Conditions*>* select_conditions,string having);

#endif