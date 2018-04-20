#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <string>
#include <iostream>

using namespace std;
enum SQLType {
	SQL_CHAR = 1,
	SQL_VARCHAR = 2,
	SQL_TEXT = 3,
	SQL_BLOB = 4,
	SQL_ENUM = 5,
	SQL_SET = 6,
	SQL_INT = 7,
	SQL_UINT = 8,
	SQL_FLOAT = 9,
	SQL_DOUBLE = 10,
	SQL_DECIMAL = 11,
	SQL_DATE = 12,
	SQL_DATETIME = 13,
	SQL_TIMESTAMP = 14,
	SQL_TIME = 15,
	SQL_YEAR = 16,
	SQL_NUMERIC = 17,
	SQL_MONEY = 18,
	SQL_REAL = 19,
	SQL_BOOL = 20
}; 

enum CCppType{
	CPP_STRING = 21,
	CPP_INT64 = 22,
	CPP_INT  = 22,
	CPP_FLOAT = 23,
	CPP_DOUBLE = 24,
	CPP_DATE = 25,
	CPP_RAW = 26,
	CPP_VECTOR = 27
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