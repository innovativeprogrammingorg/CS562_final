#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <string>
#include <iostream>
#include <vector>

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
 * Conversion table 
 * VARCHAR, CHAR, TEXT -> string
 * SET, ENUM -> vector
 * INT,UINT,YEAR, TIMESTAMP -> int64_t
 * FLOAT -> float
 * DOUBLE -> double
 * DECIMAL -> string
 * DATE, DATETIME, TIME -> string
 * NUMERIC, MONEY, REAL -> string 
 * 
 */
class Column{
	public:
		/**
		 * Column Type
		 */
		int type;
		/**
		 * Column Type in C++
		 */
		int ctype;
		/**
		 * Column Name
		 */
		string name;
		Column(string name,int type);
		Column(string name,string type);
		/**
		 * Get a string of the C++ type for the given type
		 * @param  type Either a CCPPType or SQLType
		 * @return      A string representing a C++ type
		 */
		static string getOutCppType(int type);

		/**
		 * Checks whether the column exists in the table
		 * @param  col     The column name to be tested
		 * @param  columns The columns in the table
		 * @return         Whether the column exists in the table
		 */
		static bool isColumn(string col,vector<Column*>* columns);

		static bool hasColumn(string str, vector<Column*>* columns);
	private:
		/**
		 * Gets the CPPType from the SQL type
		 * @param  type SQL type
		 * @return      CPPType
		 */
		static int getCppType(int type);

		/**
		 * Get the SQL type from a string
		 * @param  type The type of the column
		 * @return      SQLType
		 */
		static int getType(string type);	
};

#endif