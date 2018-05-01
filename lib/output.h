#ifndef _OUTPUT_H_
#define _OUTPUT_H_


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "str.h"
#include "io.h"
#include "objects/sql.h"
#include "structures.h"
#include "query.h"
#include "helpers.h"
#include "config.h"
#include "objects/conditions.h"
#include "objects/column.h"
#include "objects/aggregate.h"
#include "objects/scan_generator.h"

using namespace std;

/**
 * Get the columns of the tables and their respective types
 */
vector<Column*>* getColumns();

/**
 * Get all of the aggregates of the query
 */
vector<Aggregate*>* getAllAggregates(vector<string>* f_vect);

/**
 * Get the aggregates which appear in the select statement and the columns which appear in the select statement, as different variables
 */
vector<Aggregate*>* getSelectAggregates(vector<string>* select_attribute,vector<string>** select_columns);

/**
 * Processes the query and outputs the program which executes the query
 */
void parse_query(vector<string>*,string, int, vector<string>*, vector<string>*, vector<string>*,string,bool);


#ifndef OUTPUT_FILE
#define OUTPUT_FILE "./result.cpp"
#endif

#ifndef OUTPUT_FILE_HEADER_LOCATION
#define OUTPUT_FILE_HEADER_LOCATION "./result.h"
#endif
 
#ifndef OUTPUT_FILE_HEADER_START
#define OUTPUT_FILE_HEADER_START "#ifndef _RESULT_H_\n" \
	"#define _RESULT_H_ \n" \
	"#include <string>\n" \
	"#include <vector>\n" \
	"#include <cstdint>\n" \
	"#include <map>\n"  \
	"#include <cppconn/resultset.h>\n" \
	"#include \"lib/str.h\"\n" \
	"#include \"lib/objects/average.h\"\n" \
	"#include \"lib/objects/sql.h\"\n" \

#endif

#ifndef OUTPUT_FILE_HEADER_END
#define OUTPUT_FILE_HEADER_END "#endif"
#endif


#endif