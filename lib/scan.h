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

/**
 * Creates helper functions for the final output program
 * @param  no_grouping_vars The number of grouping variables
 * @param  select_columns   The columns in the select statement
 * @param  columns          The columns in the table
 * @return                  The helper functions for the program
 */
string get_helpers(int no_grouping_vars, vector<string>* select_columns, vector<Column*>* columns);




/**
 * Generates all 3 scans
 * @param  no_grouping_vars  The number of grouping variables
 * @param  columns           The columns in the table
 * @param  select_columns    The columns in the select statement
 * @param  select_aggregates The aggregates in the select statement
 * @param  all_aggregates    All of the aggregates
 * @param  select_conditions The such that logic for each grouping variable
 * @param  having            The having string
 * @return                   All 3 scans used for processing
 */
string create_scans(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* select_aggregates,
				    vector<Aggregate*>* all_aggregates,vector<Conditions*>* select_conditions,string having);

#endif