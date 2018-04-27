#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <vector>
#include <string>
#include <iostream>
#include "objects/column.h"
#include "objects/aggregate.h"

/**
 * Creates a function that prints out the contents of the 
 * mf structure 
 * @param  select_attribute The select attributes
 * @param  columns          The columns in the table
 * @return                  A string of the function
 */
string create_output_printer(vector<string>* select_attribute,vector<Column*>* columns);

/**
 * Creates the structures for the mf structure and the data loaded from the database
 * @param  select_attribute The select attributes
 * @param  columns          The columns in the table
 * @return                  A string of the structures
 */
string create_structures(vector<string>* select_attribute,vector<Column*>* columns);

/**
 * Creates the structures for the grouping variables
 * @param  no             The number of grouping variables
 * @param  columns        The columns in the table
 * @param  select_columns The columns in the select attribute
 * @param  all_aggregates All of the aggregates in the query
 * @return                A string of the grouping variable structures
 */
string create_grouping_var_structs(int no,vector<Column*>* columns,vector<string>* select_columns,vector<Aggregate*>* all_aggregates);

#endif