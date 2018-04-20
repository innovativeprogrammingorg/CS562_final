#include "column.h"

using namespace std;

Column::Column(string name,int type){
	this->name = name;
	this->type = type;
	this->ctype = Column::getCppType(this->type);
}

Column::Column(string name,string type){
	this->name = name;
	this->type = Column::getType(type);
	this->ctype = Column::getCppType(this->type);
}
string Column::getOutCppType(int type){
	switch(type){
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_TEXT:
		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_MONEY:
		case SQL_REAL:
		case CPP_STRING:
		{
			return "string";
		}
		case SQL_BLOB:
		{
			return "uint8_t[10000]";
		}
		case SQL_ENUM:
		case SQL_SET:
		{
			return "vector<string>";
		}
		case CPP_INT64:
		case SQL_YEAR:
		case SQL_INT:
		case SQL_TIMESTAMP:
		case SQL_UINT:
		{
			return "int64_t";
		}
		case CPP_FLOAT:
		case SQL_FLOAT:
		{
			return "float";
		}
		case CPP_DOUBLE:
		case SQL_DOUBLE:
		{
			return "double";
		}
		case SQL_DATE:
		case SQL_DATETIME:
		case SQL_TIME:
		{
			return "Date";
		}
	
		
		
		
		
	}
	return "";
}


int Column::getCppType(int type){
	switch(type){
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_TEXT:
		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_MONEY:
		case SQL_REAL:
		{
			return CPP_STRING;
		}
		case SQL_BLOB:
		{
			return CPP_RAW;
		}
		case SQL_ENUM:
		case SQL_SET:
		{
			return CPP_VECTOR;
		}
		case SQL_YEAR:
		case SQL_INT:
		case SQL_TIMESTAMP:
		case SQL_UINT:
		{
			return CPP_INT64;
		}
	
		case SQL_FLOAT:
		{
			return CPP_FLOAT;
		}
		case SQL_DOUBLE:
		{
			return CPP_DOUBLE;
		}
		case SQL_DATE:
		case SQL_DATETIME:
		case SQL_TIME:
		{
			return CPP_DATE;
		}
		
	}
	return CPP_INT64;
}

int Column::getType(string type){
	if(type.find("varchar")!=string::npos){
		return SQL_VARCHAR;	
	}else if(type.find("char")!=string::npos){
		return SQL_CHAR;
	}else if(type.find("text")!=string::npos){
		return SQL_TEXT;
	}else if(type.find("enum")!=string::npos){
		return SQL_ENUM;
	}else if(type.find("set")!=string::npos){
		return SQL_SET;
	}else if(type.find("unsigned")!=string::npos){
		return SQL_UINT;
	}else if(type.find("int")!=string::npos){
		return SQL_INT;
	}else if(type.find("float")!=string::npos){
		return SQL_FLOAT;
	}else if(type.find("double")!=string::npos){
		return SQL_DOUBLE;
	}else if(type.find("decimal")!=string::npos){
		return SQL_DECIMAL;
	}else if(type.find("datetime")!=string::npos){
		return SQL_DATETIME;
	}else if(type.find("timestamp")!=string::npos){
		return SQL_TIMESTAMP;
	}else if(type.find("time")!=string::npos){
		return SQL_TIME;
	}else if(type.find("date")!=string::npos){
		return SQL_DATE;
	}else if(type.find("year")!=string::npos){
		return SQL_YEAR;
	}else if(type.find("blob")!=string::npos){
		return SQL_BLOB;
	}else if(type.find("numeric")!=string::npos){
		return SQL_NUMERIC;
	}else if(type.find("money")!=string::npos){
		return SQL_MONEY;
	}else if(type.find("real")!=string::npos){
		return SQL_REAL;
	}
	return SQL_BOOL;
}