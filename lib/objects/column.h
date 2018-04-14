#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <string>

using namespace std;
enum SQLType {
	SQL_CHAR,
	SQL_VARCHAR,
	SQL_TEXT,
	SQL_BLOB,
	SQL_ENUM,
	SQL_SET,
	SQL_INT,
	SQL_UINT,
	SQL_FLOAT,
	SQL_DOUBLE,
	SQL_DECIMAL,
	SQL_DATE,
	SQL_DATETIME,
	SQL_TIMESTAMP,
	SQL_TIME,
	SQL_YEAR,
	SQL_NUMERIC,
	SQL_MONEY,
	SQL_REAL,
	SQL_BOOL
}; 

enum CCppType{
	CPP_STRING,
	CPP_INT64,
	CPP_FLOAT,
	CPP_DOUBLE,
	CPP_DATE,
	CPP_RAW,
	CPP_VECTOR
};


/**
 * For simplicity's sake, for the time being, the max size is not being included
 * This could be represented as a struct, but for simplicity, it is a class
 * Conversion table 
 * VARCHAR, CHAR, TEXT -> string
 * SET, ENUM -> vector
 * INT -> int64_t
 * UINT -> int64_t
 * FLOAT -> float
 * DOUBLE -> double
 * DECIMAL -> string
 * DATE, DATETIME, TIME ->string
 * TIMESTAMP -> time_t
 * Year -> int
 * NUMERIC, MONEY, REAL -> string 
 * 
 */
class Column{
	public:
		int type;
		int ctype;
		string name;
		Column(string name,int type);
		Column(string name,string type);
		static string getOutCppType(int type);
	private:
		static int getCppType(int type);
		static int getType(string type);	
};


#endif