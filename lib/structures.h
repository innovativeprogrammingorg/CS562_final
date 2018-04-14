#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <vector>
#include <string>
#include "objects/column.h"
#include "objects/aggregate.h"



string create_structures(vector<string>* select_attribute,vector<Column*>* columns);
string create_grouping_var_structs(int no,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* all_aggregates);

#endif