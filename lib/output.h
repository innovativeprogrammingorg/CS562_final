#ifndef _OUTPUT_H_
#define _OUTPUT_H_


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "str.h"
#include "io.h"
#include "objects/sql.h"
#include "objects/column.h"
#include "objects/value.h"


using namespace std;
void parse_query(vector<string>*, int, vector<string>*, vector<string>*, vector<string>*,string);

#ifndef COLUMN_TYPE_QUERY
#define COLUMN_TYPE_QUERY "SELECT * FROM `COLUMNS` WHERE `TABLE_NAME` = \'sales\' AND `TABLE_SCHEMA` = \'CS562\'"
#endif

#ifndef OUTPUT_FILE
#define OUTPUT_FILE "./result.cpp"
#endif

#ifndef OUTPUT_FILE_HEADER_LOCATION
#define OUTPUT_FILE_HEADER_LOCATION "./result.h"
#endif
 
#ifndef OUTPUT_FILE_HEADER
#define OUTPUT_FILE_HEADER "#ifndef _RESULT_H_\n" \
	"#define _RESULT_H_ \n" \
	"#include <string>" 

#endif


#endif