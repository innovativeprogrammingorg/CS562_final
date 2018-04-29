#ifndef _QUERY_H_
#define _QUERY_H_


#include <vector>
#include <string>
#include "config.h"
#include "objects/column.h"
#include "objects/aggregate.h"

using namespace std;

string get_sql_res_function(int type);

string data_retrieval(int no_grouping_vars,vector<Column*>* columns,vector<string>* select_columns,vector<string>* select_cond_vect,
					  vector<Aggregate*>* all_aggregates,vector<string>* grouping_attr,string where);
#endif