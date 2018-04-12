#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <string>

enum CType = {
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

/**
 * For simplicity's sake, for the time being, the max size is not being included
 * This could be represented as a struct, but for simplicity, it is a class
 * Conversion table 
 * VARCHAR, CHAR, TEXT -> string
 * SET, ENUM -> vector
 * INT -> int64_t
 * UINT -> uint64_t
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
		CType type;
		string name;
		Column(string name,CType type);
		Column(string name,string type);
	private:
		static CType getType(string type);	
}


#endif