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
#include "scan.h"
#include "objects/column.h"
#include "objects/aggregate.h"


using namespace std;
vector<Column*>* getColumns();
vector<Aggregate*>* getAllAggregates(vector<string>* f_vect);
void parse_query(vector<string>*, int, vector<string>*, vector<string>*, vector<string>*,string);


#ifndef TABLE
#define TABLE "sales"
#endif

#ifndef DATABASE
#define DATABASE "CS562"
#endif

#ifndef COLUMN_TYPE_QUERY
#define COLUMN_TYPE_QUERY "SELECT * FROM `COLUMNS` WHERE `TABLE_NAME` = \'sales\' AND `TABLE_SCHEMA` = \'CS562\'"
#endif

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
	"#include \"lib/objects/sql.h\"\n" 

#endif

#ifndef OUTPUT_FILE_HEADER_END
#define OUTPUT_FILE_HEADER_END "#endif"
#endif


#endif