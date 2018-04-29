#ifndef _QUERY_H_
#define _QUERY_H_


#include <vector>
#include <string>
#include "config.h"
#include "objects/column.h"
#include "objects/aggregate.h"

using namespace std;

/**
 * Resolves the type into the appropiate function in the 
 * mysql connect library
 * @param  type The type of the column
 * @return      The fuction capable of fetching it
 */
string get_sql_res_function(int type);

/**
 * Generates code which fetches the data from the table and
 * puts it in a data structure
 * @param  columns The table's columns
 * @param  where   The query where clause
 * @return         The code
 */
string data_retrieval(vector<Column*>* columns,string where);
#endif